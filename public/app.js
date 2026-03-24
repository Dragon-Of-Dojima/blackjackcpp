const API = '';

const SCALE = 80 / 359;
const ORIGIN_X = 30.5 * SCALE;
const ORIGIN_Y = 30.5 * SCALE;
const STRIDE_X = 390 * SCALE;
const STRIDE_Y = 570 * SCALE;

const SUIT_ROW = {
	'Spades': 0,
	'Hearts': 1,
	'Diamonds': 2,
	'Clubs': 3
};

const FACE_COL = {
	'A': 0, '2': 1, '3': 2, '4': 3, '5': 4, '6': 5, '7': 6,
	'8': 7, '9': 8, '10': 9, 'J': 10, 'Q': 11, 'K': 12
};

function createCardEl(face, suit) {
	const div = document.createElement('div');
	div.className = 'card';

	if (face === 'hidden') {
		div.classList.add('facedown');
	} else {
		const col = FACE_COL[face];
		const row = SUIT_ROW[suit];
		const x = ORIGIN_X + col * STRIDE_X;
		const y = ORIGIN_Y + row * STRIDE_Y;
		div.style.backgroundPosition = `-${x}px -${y}px`;
	}

	return div;
}

function renderCards(containerId, cards) {
	const container = document.getElementById(containerId);
	container.innerHTML = '';
	cards.forEach(c => container.appendChild(createCardEl(c.face, c.suit)));
}

function renderScore(elementId, score, soft) {
	const el = document.getElementById(elementId);
	if (score === 0) {
		el.innerHTML = '';
	} else if (soft) {
		el.innerHTML = `${score - 10} or ${score}`;
	} else {
		el.innerHTML = `${score}`;
	}
}

function setMessage(text, className) {
	const el = document.getElementById('message');
	el.textContent = text;
	el.className = className || '';
}

function setButtons(canDeal, canPlay) {
	document.getElementById('btn-deal').disabled = !canDeal;
	document.getElementById('btn-hit').disabled = !canPlay;
	document.getElementById('btn-stay').disabled = !canPlay;
}

function updateUI(state) {
	renderCards('player-cards', state.player.cards);
	renderCards('dealer-cards', state.dealer.cards);
	renderScore('player-score', state.player.score, state.player.soft);
	renderScore('dealer-score', state.dealer.score, state.dealer.soft);

	const STATUS_MAP = {
		'player_turn':      { msg: '',                    cls: '',          deal: false, play: true },
		'player_bust':      { msg: 'Busted!',             cls: 'lose',      deal: true,  play: false },
		'player_blackjack': { msg: 'Blackjack!',          cls: 'blackjack', deal: true,  play: false },
		'player_21':        { msg: '21!',                  cls: 'win',       deal: false, play: false },
		'dealer_bust':      { msg: 'Dealer busts! You win!', cls: 'win',    deal: true,  play: false },
		'player_win':       { msg: 'You win!',             cls: 'win',       deal: true,  play: false },
		'dealer_win':       { msg: 'Dealer wins.',         cls: 'lose',      deal: true,  play: false },
		'push':             { msg: 'Push.',                cls: 'push',      deal: true,  play: false },
		'waiting':          { msg: 'Press Deal to start.', cls: '',          deal: true,  play: false }
	};

	const s = STATUS_MAP[state.status] || STATUS_MAP['waiting'];
	setMessage(s.msg, s.cls);
	setButtons(s.deal, s.play);

	if (state.status === 'player_21') {
		stay();
	}
}

async function deal() {
	const res = await fetch(API + '/api/deal', { method: 'POST' });
	const state = await res.json();
	updateUI(state);
}

async function hit() {
	const res = await fetch(API + '/api/hit', { method: 'POST' });
	const state = await res.json();
	updateUI(state);
}

async function stay() {
	const res = await fetch(API + '/api/stay', { method: 'POST' });
	const state = await res.json();
	updateUI(state);
}

setMessage('Press Deal to start.', '');
setButtons(true, false);
