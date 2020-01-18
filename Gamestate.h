#pragma once



class Game;

//jweiliger spielstatus: Hauptmenue, Pause , Spiel , Optionen

class Gamestate
{

	

public:
	Gamestate();
	virtual ~Gamestate();
	virtual void HandleEvents(Game &game) = 0;
	virtual void Update(Game &game) = 0;
	virtual void Draw(Game &game) = 0;

};

