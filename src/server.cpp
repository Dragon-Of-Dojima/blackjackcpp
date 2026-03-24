#include "httplib.h"
#include "json.hpp"
#include "Game.h"
#include <iostream>
#include <map>
#include <mutex>
#include <random>

using json = nlohmann::json;

std::map<std::string, Game> sessions;
std::mutex mtx;

std::string generateSessionId() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dist(0, 15);
	const char* hex = "0123456789abcdef";
	std::string id;
	for (int i = 0; i < 32; i++) {
		id += hex[dist(gen)];
	}
	return id;
}

std::pair<std::string, Game&> getGame(const httplib::Request& req) {
	std::string sid;
	if (req.has_param("sid")) {
		sid = req.get_param_value("sid");
	}
	if (sid.empty() || sessions.find(sid) == sessions.end()) {
		sid = generateSessionId();
		sessions[sid] = Game();
	}
	return {sid, sessions[sid]};
}

json handToJson(const Hand& hand, bool hideHoleCard = false){
	json cards = json::array();
	const auto& cardlist = hand.getCards();
	for(int i = 0; i < (int)cardlist.size(); i++){
		if(hideHoleCard && i == 0){
			cards.push_back({{"face", "hidden"}, {"suit", "hidden"}});
		}else{
			cards.push_back({
				{"face", cardlist[i].getCardValue().getFace()},
				{"suit", suitToString(cardlist[i].getSuit())}
			});
		}
	}
	return cards;
}

json gameStateToJson(const Game& game, const std::string& sid){
	bool hideDealer = (game.getStatus() == PLAYER_TURN);
	json state = {
		{"sid", sid},
		{"status", game.statusToString()},
		{"player", {
			{"cards", handToJson(game.getPlayerHand())},
			{"score", game.getPlayerHand().getScore()},
			{"soft", game.getPlayerHand().isSoft()}
		}},
		{"dealer", {
			{"cards", handToJson(game.getDealerHand(), hideDealer)},
			{"score", hideDealer
				? game.getDealerHand().getCards()[1].getCardValue().getNumeric()
				: game.getDealerHand().getScore()},
			{"soft", hideDealer
				? (game.getDealerHand().getCards()[1].getCardValue().getNumeric() == 11)
				: game.getDealerHand().isSoft()}
		}}
	};
	return state;
}

int main(){
	httplib::Server svr;

	svr.Post("/api/deal", [](const httplib::Request& req, httplib::Response& res){
		std::lock_guard<std::mutex> lock(mtx);
		auto [sid, game] = getGame(req);
		game.deal();
		res.set_content(gameStateToJson(game, sid).dump(), "application/json");
	});

	svr.Post("/api/hit", [](const httplib::Request& req, httplib::Response& res){
		std::lock_guard<std::mutex> lock(mtx);
		auto [sid, game] = getGame(req);
		game.hit();
		res.set_content(gameStateToJson(game, sid).dump(), "application/json");
	});

	svr.Post("/api/stay", [](const httplib::Request& req, httplib::Response& res){
		std::lock_guard<std::mutex> lock(mtx);
		auto [sid, game] = getGame(req);
		game.stay();
		res.set_content(gameStateToJson(game, sid).dump(), "application/json");
	});

	svr.Get("/api/state", [](const httplib::Request& req, httplib::Response& res){
		std::lock_guard<std::mutex> lock(mtx);
		auto [sid, game] = getGame(req);
		res.set_content(gameStateToJson(game, sid).dump(), "application/json");
	});

	auto ret = svr.set_mount_point("/", "./public");
	if (!ret) {
		std::cerr << "Failed to mount ./public  — directory not found from cwd" << std::endl;
	} else {
		std::cout << "Serving static files from ./public" << std::endl;
	}

	std::cout << "Blackjack server running on port 8081" << std::endl;
	svr.listen("0.0.0.0", 8081);
}
