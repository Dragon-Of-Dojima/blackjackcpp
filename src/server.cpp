#include "httplib.h"
#include "json.hpp"
#include "Game.h"
#include <iostream>

using json = nlohmann::json;

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

json gameStateToJson(const Game& game){
	bool hideDealer = (game.getStatus() == PLAYER_TURN);
	json state = {
		{"status", game.statusToString()},
		{"player", {
			{"cards", handToJson(game.getPlayerHand())},
			{"score", game.getPlayerHand().getScore()},
			{"soft", game.getPlayerHand().isSoft()}
		}},
		{"dealer", {
			{"cards", handToJson(game.getDealerHand(), hideDealer)},
			{"score", hideDealer ? 0 : game.getDealerHand().getScore()},
			{"soft", hideDealer ? false : game.getDealerHand().isSoft()}
		}}
	};
	return state;
}

int main(){
	Game game;
	httplib::Server svr;

	svr.Post("/api/deal", [&game](const httplib::Request&, httplib::Response& res){
		game.deal();
		res.set_content(gameStateToJson(game).dump(), "application/json");
	});

	svr.Post("/api/hit", [&game](const httplib::Request&, httplib::Response& res){
		game.hit();
		res.set_content(gameStateToJson(game).dump(), "application/json");
	});

	svr.Post("/api/stay", [&game](const httplib::Request&, httplib::Response& res){
		game.stay();
		res.set_content(gameStateToJson(game).dump(), "application/json");
	});

	svr.Get("/api/state", [&game](const httplib::Request&, httplib::Response& res){
		res.set_content(gameStateToJson(game).dump(), "application/json");
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
