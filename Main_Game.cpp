#include "Main_Game.h"
#include <iostream>

//leonardo-boccuti genaro1234 web.de

//bei sfml dev or 
//bei view ist eine  gute möglichkeit gezeigt wie man eine minimap oben rechts macht
//assi gut, das einfügen


//ich muss für gegner kollision richtig machen, damit sie nicht 
//ineinander kleben bleiben, dazu müsste wissen wo der gegner kollidiert
//und entsprechend in die andere richtung zurück schieben

//projektil konstruktor texture übergeben und vorher textureladen
//im konsturkor dann nur noch sprite texture geben
//weiol der zeit lade ich im konstruktor sogar die texture



//player und npc und evtl noch items mit entitiy aufräumen


//wenn spieler enemy beührt schauen wo kollidiert
//oben unten rechts links und dementsprechend den charakter
//weg pushen


Main_Game::Main_Game(sf::Vector2i screenDimensions)
{
	

	//load all shit from binary file
	//dont forget to create new one if graphic changes
	bool loadfromfile = 0;

	if (loadfromfile)
	{
		assetmanager.LoadFromFile();
	}
	else assetmanager.LoadAllTexturesFromImages();

	assetmanager.LoadFont("font", "Spiel_Projekt_Protectyourisle_Assets\\Fonts\\kamikaze.ttf");
	assetmanager.LoadSound("treesound", "Spiel_Projekt_Protectyourisle_Assets\\Sounds\\crack02.flac");
	assetmanager.LoadSound("Swordswing", "Spiel_Projekt_Protectyourisle_Assets\\Sounds\\swing.wav");
	assetmanager.LoadSound("Fireballsound", "Spiel_Projekt_Protectyourisle_Assets\\Sounds\\Fireballsound.wav");
	assetmanager.LoadSound("Electrichitsound", "Spiel_Projekt_Protectyourisle_Assets\\Sounds\\Electrichitsound.flac");
	assetmanager.LoadSound("Snowballsound", "Spiel_Projekt_Protectyourisle_Assets\\Sounds\\Snowballsound.flac");
	assetmanager.LoadSound("Lvupsound", "Spiel_Projekt_Protectyourisle_Assets\\Sounds\\Lvupsound.wav");
	assetmanager.LoadSound("Kachingsound", "Spiel_Projekt_Protectyourisle_Assets\\Sounds\\coin.wav");
	assetmanager.LoadSound("nomana1", "Spiel_Projekt_Protectyourisle_Assets\\Sounds\\nomanatyler1.wav");
	assetmanager.LoadSound("nomana2", "Spiel_Projekt_Protectyourisle_Assets\\Sounds\\nomanatyler2.wav");

	items.initSprites(assetmanager);
	items.initScreenDimension(screenDimensions);

	Spieler1 = std::unique_ptr<Player>(new Player(sf::Vector2f(400,500), &assetmanager.GetTexture("playertexture"),
		&assetmanager.GetTexture("weaponset")));


	lvhandler.InitLevels(&assetmanager);
	gui.init(&assetmanager,&sh, Spieler1.get());
	eh.ptrTileMapWithCollision = &TileMapPainter;
	eh.init_player_ptr(Spieler1);
	eh.connect_to_texthandler(TextManager);
	eh.connect_to_SoundHandler(sh);

	TileMapPainter.set_map(lvhandler.getLevel("Mountain"));
	//texturen init und so
	eh.connectToAssets(assetmanager);
	sh.init(assetmanager);
	TextManager.init(*assetmanager.ptr_GetFont("font"), assetmanager.GetTexture("textbox"));

	//view.setSize(1000, 600);
	view.setSize(1000, 600);

	activatecollision = true;
	
	//getlevelenemyspawnmodi -> level class machen die details +ber das level hat dementsprechend auch die enems die darin spawnen 
	eh.changeSpawnModi(3);

	TileMapPainter.InitShaderShit();
}


Main_Game::~Main_Game()
{
	


}



void Main_Game::HandleEvents(Game & game)
{
	sf::Event e;
		

	while (game.window.pollEvent(e)) {

		mousepos = sf::Mouse::getPosition(game.window);

		if (e.type == sf::Event::Closed) {
			game.window.close();
			game.stoprunning();
		}

		if (e.key.code == sf::Keyboard::Escape) {

			//hat gezickt weil view in main game war, und maingame ist ja ein shared pointer und wenn der aufgelöst wurde
			//war dementsprechend kein view mehr da 
			//sf::FloatRect visibleArea(0.f, 0.f, 1024, 768);
			sf::View nview(sf::FloatRect(0.f, 0.f, game.window.getSize().x, game.window.getSize().y));

			game.window.setView(nview);
			game.ChangeState(Game::Instanzen::Startmenue);
			return;//return da ssonst der scope weiter geht und da changestate ist peicherbereich nicht mehr vorhanden
			//wenn dann unten noch irgendwelche funktiopnen laufen dann crash
					
		}


		if (e.key.code == sf::Keyboard::M) {
			std::cout << "x: " << Spieler1->getPosition().x <<std:: endl;
			std::cout << "y: " << Spieler1->getPosition().y << std:: endl;
			assetmanager.createCurrentResourceAsBinaryFile();
		

			std::vector<unsigned char> test;
			test.push_back(0xf0);
			test.push_back(0x00);
			test.push_back(0x00);
			test.push_back(0xf1);
			//unsigned int te= FileMaker::getBytesAs<unsigned int>(test);
			
			unsigned int te = getBytesAs<unsigned int>(test);

			unsigned char tc = getBytesAs<unsigned char>(test);

			cout << "die zahl ist: " << te << endl;
			cout << "als char: " << tc << endl;

			
		}

		
	//achtung geht nur während etwas gedrückt wird weil wir jja gerade im pollevent drinne nsind
		handle_menues(e);
			
			if (e.mouseButton.button == sf::Mouse::Left)
			{
	
				items.getklick(sf::Vector2i(game.window.mapPixelToCoords(mousepos)));
				printf("leftklick\n");
				items.left_klick();

				if (ptr_magickblizzard != nullptr)

				{
					printf("speicherleck oder?\n");
					ptr_magickblizzard->activate();
			
					ptr_magickblizzard = nullptr;

				}
				

			}

			
			if (e.type == sf::Event::MouseButtonReleased)
			{

				if (e.mouseButton.button == sf::Mouse::Right)
				{
					if (items.is_selling()) {
						items.right_klick();
					}
				}

				if (e.mouseButton.button == sf::Mouse::Left)
				{			
					//0-4						//0-11
					gui.SetNewSkill();
				}

			}

				if (e.mouseButton.button == sf::Mouse::Left&& e.type == sf::Event::MouseButtonPressed)
				{
		
					gui.PickNewSkill();
							
				}
				if (e.mouseButton.button == sf::Mouse::Left && e.type == sf::Event::MouseButtonReleased) {
				
				}
		
 
	}
}

void Main_Game::Update(Game & game)
{	

	sh.update(game.framedeltatime);
	eh.check_for_new_enemys(TileMapPainter, game.framedeltatime);
	//für aoe spell, jetzt nur noch dem player geben.
	mousepos = sf::Mouse::getPosition(game.window);
	//Spieler1->mousepos = game.window.mapPixelToCoords(mousepos);

	sf::Vector2f rainpos;
	rainpos.x = rand() % 1280;
	rainpos.y = (Spieler1->getPosition().y-380);

	if (TileMapPainter.collide_engine(Spieler1->getPosition(),sf::Vector2f(0,0))) {
		Spieler1->movementComponent->setCollide();


	}
	else {

		//sonst ruckelt gui und charaktersprite
		//vorher war setcenter ueber setview und gui update immer
		camerapos = sf::Vector2i(Spieler1->getPosition().x, Spieler1->getPosition().y);
		//kante oben links
		if (camerapos.x < 500)camerapos.x = 500;
		if (camerapos.y < 320)camerapos.y = 320;
		if (camerapos.x > 760)camerapos.x = 760;

		//kante unten links
		if (camerapos.y >(TileMapPainter.get_map_height()*32)-300)camerapos.y = TileMapPainter.get_map_height()*32-300 ;

		view.setCenter(sf::Vector2f(camerapos.x,camerapos.y));
		gui.update(sf::Vector2f(camerapos.x, camerapos.y),game.framedeltatime, game.window.mapPixelToCoords(mousepos));
	}


	handle_player(game);
	game.window.setView(view);	
	handle_items(game);


	if (Spieler1->attributs.isalive()) {
		


	}

	
	if (Spieler1->attributs.getxp_andlvup(eh.get_xp_from_enemys())) {
		//gui.change_levelstring(Spieler1->attributs.get_level());
		//gui.fillxpbar(xp);
		printf("spieler sollte lv up sein \n");
		sh.playSound("Lvupsound");
	}
	
	//textboxmanager.update(Spieler1->getplayerpos());
	
	eh.update(items,game.framedeltatime,Spieler1->getPosition());
	TextManager.update(game.framedeltatime,Spieler1->getPosition());
	changeLevelExtended();

}


void Main_Game::Draw(Game & game)
{


	TileMapPainter.draw_layer1(game.window);

	items.draw(game.window);
	items.draw_diamonds(game.window);

	Spieler1->draw(game.window);
	eh.draw(game.window);//entitiys all
	
	TileMapPainter.draw_layer2(game.window);

	gui.draw(game.window);


	if (showinventory) {
	
		items.draw_inventory(game.window);

	}

	if (showequip) {
		items.draw_euqip(game.window);
	}

	if (bweather_on) {
		game.window.draw(*wetter);
	}

	
	TextManager.draw(game.window);


	//sf::FloatRect wpRect = Spieler1->playerweapon->getCollRect();
	//sf::RectangleShape rect;
	//rect.setSize(sf::Vector2f(wpRect.width, wpRect.height));
	//rect.setFillColor(sf::Color::Red);
	//rect.setPosition(sf::Vector2f(wpRect.left,wpRect.top));
	//

	//game.window.draw(rect);


	
}

void Main_Game::handle_menues(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed) {

		if (e.key.code == sf::Keyboard::Z) gui.toggleSkillmenue();


		if (e.key.code == sf::Keyboard::C) {

			if (showequip) {
				showequip = false;
			}
			else {
				showequip = true;
			}

		}
	
	
		if (e.key.code == sf::Keyboard::I) {

			if (showinventory) {
				showinventory = false;
			}
			else {
				showinventory = true;
			}


		}
	}//hier hört keypress auf

	//0xDDDDDDDD lesezugriffsverletzung, da unique pointer verschoben wurde und dann darauf zugegriffen :D
	//das problem war das die handle events noch ausgeführt wurde
	//in der handle events ist handle menues und darauf wird dann zugrgriffen obowhl der
	//pointer schon verschoben wurde... aber durch return nach escape wird sofort aus handle
	//events rausgesprungen :D, elegant gelöst =)


	//gui.fillxpbar(Spieler1->attributs.getxpaspercent());

}


void Main_Game::changeLevelExtended()
{
	bool haveChanged = false;
	sf::Vector2f pos = Spieler1->getPosition();


	 if (lvhandler.ECurrentLevel == eMaps::DesertBossGround && pos.y <64 && pos.x >350) {
		

		 TileMapPainter.set_map(lvhandler.getLevel("BossGround"));
		
			lvhandler.ECurrentLevel = eMaps::BossGround;
			Spieler1->setplayerpos(sf::Vector2f(701, 888));
			haveChanged = true;
			eh.changeSpawnModi(4);
			sh.playMusic("BossMusic");
			
		}
	

		//if currentmap gleich montaint

		else if (lvhandler.ECurrentLevel == eMaps::Mountain && pos.y < 32 && (pos.x >95&& pos.x < 175)) {
	

		 TileMapPainter.set_map(lvhandler.getLevel("Homeland"));
	
			lvhandler.ECurrentLevel = eMaps::start;
			Spieler1->setplayerpos(sf::Vector2f(629, 888));
			haveChanged = true;
			eh.changeSpawnModi(0);
			sh.playMusic("HomeMusic");
			
			
		}


		else if (lvhandler.ECurrentLevel == eMaps::start && pos.y > 910 && pos.x > 544) {
	

		 TileMapPainter.set_map(lvhandler.getLevel("Mountain"));
		 Spieler1->setplayerpos(sf::Vector2f(132, 32));
			lvhandler.ECurrentLevel = eMaps::Mountain;
			haveChanged = true;
			eh.changeSpawnModi(2);
			sh.playMusic("WoodMusic");

		}

		else if (lvhandler.ECurrentLevel == eMaps::BossGround&& pos.y > 914 && pos.x > 640) {
	

		 TileMapPainter.set_map(lvhandler.getLevel("DesertBoss"));
		 Spieler1->setplayerpos(sf::Vector2f(799, 95));
			lvhandler.ECurrentLevel = eMaps::DesertBossGround;
			haveChanged = true;
			eh.changeSpawnModi(1);
			sh.stopMusic();
		}
	


		else if (lvhandler.ECurrentLevel == eMaps::Mountain && pos.y > 570 && pos.x >1258) {
		

		 TileMapPainter.set_map(lvhandler.getLevel("Desert"));
		 Spieler1->setplayerpos(sf::Vector2f(71, 536));
			lvhandler.ECurrentLevel = eMaps::Desert;
			haveChanged = true;
			eh.changeSpawnModi(1);
			sh.playMusic("DesertMusic");
		}

		else if (lvhandler.ECurrentLevel == eMaps::Mountain && pos.y > 885 && pos.x > 850) {
		

		 TileMapPainter.set_map(lvhandler.getLevel("Town"));
		 Spieler1->setplayerpos(sf::Vector2f(1032, 51));
			lvhandler.ECurrentLevel = eMaps::Town;
			haveChanged = true;
			eh.changeSpawnModi(0);
			sh.playMusic("TownMusic");
		
		}

		else if (lvhandler.ECurrentLevel == eMaps::Desert && pos.y > 505 && pos.x < 1) {
	

		 TileMapPainter.set_map(lvhandler.getLevel("Mountain"));
		 Spieler1->setplayerpos(sf::Vector2f(1172, 605));
			lvhandler.ECurrentLevel = eMaps::Mountain;
			haveChanged = true;
			eh.changeSpawnModi(3);
			sh.playMusic("WoodMusic");
			
		}
	
		else if (lvhandler.ECurrentLevel == eMaps::Desert && pos.y > 440 && pos.x > 1260) {
	
		 TileMapPainter.set_map(lvhandler.getLevel("DesertBoss"));
		 Spieler1->setplayerpos(sf::Vector2f(71, 536));
			lvhandler.ECurrentLevel = eMaps::DesertBossGround;
			haveChanged = true;
			eh.changeSpawnModi(1);
			sh.stopMusic();
		}
		else if (lvhandler.ECurrentLevel == eMaps::DesertBossGround&& pos.y > 440 && pos.x < 10) {
		
		 TileMapPainter.set_map(lvhandler.getLevel("Desert"));
		 Spieler1->setplayerpos(sf::Vector2f(1172, 605));
		 lvhandler.ECurrentLevel = eMaps::Desert;
		 haveChanged = true;
		 eh.changeSpawnModi(1);
		 sh.playMusic("DesertMusic");
	   }


		else if (lvhandler.ECurrentLevel == eMaps::Town && Spieler1->getPosition().y < 0) {
	

		TileMapPainter.set_map(lvhandler.getLevel("Mountain"));
		Spieler1->setplayerpos(sf::Vector2f(939, 879));
			lvhandler.ECurrentLevel = eMaps::Mountain;
			haveChanged = true;
			eh.changeSpawnModi(3);
			sh.playMusic("WoodMusic");
		}
	


	if (haveChanged)
	{
		eh.killAllEntitys();
		eh.asterngetuned.resetObstacles(TileMapPainter);
		TileMapPainter.load_from_map();

		if (lvhandler.ECurrentLevel == eMaps::start)
			eh.PopAlotOfButterflys(sf::Vector2f(1000.f,700.f));
	}

}


//now draw
void Main_Game::handle_items(Game & game)
{
	sf::Vector2f mouse_pos = game.mousePosView;
	

	items.update(game.framedeltatime,sf::Vector2i(mouse_pos), Spieler1->getPosition(),Spieler1->attributs);
	items.clear_item_vector();

	items.diamond_all(sf::Vector2i(mouse_pos), Spieler1->getPosition(), game.framedeltatime);

	
	if (showinventory) {
		items.update_inventory(game.framedeltatime, sf::Vector2i(game.window.mapPixelToCoords(mousepos)),sf::Vector2f( camerapos));
	}

	if (showequip) {
		items.update_equip(sf::Vector2i(game.window.mapPixelToCoords(mousepos)), sf::Vector2f(camerapos));
	}

	//sound wird in gui abgespielt!!
	if (items.got_money())gui.give_money(items.get_earned_money());

	Spieler1->playerweapon->change_weapon(items.get_equipped_sword());
	Spieler1->attributs.setEqAtk( items.get_dmg_from_eq());

}

void Main_Game::handle_player(Game & game)
{
	//zauber int der update mitgeben
	Spieler1->update(game.framedeltatime,sf::Vector2f());
	/*std::cout << game.framedeltatime.asSeconds() << std::endl;*/
	//Spieler1->isAttacking = eh.wp->attack;

	sf::Vector2f pp = Spieler1->getPosition();
	mousepos = sf::Mouse::getPosition(game.window);
		

	MagickBlizzard *mb;



	//hier findet die magie statt, evtl texture übergeben bzw dem konstsruktor von projektil
	//Spieler1->set_spell( gui.return_choosen_spell(), game.framedeltatime);
	int id = gui.return_choosen_spell();
	switch (id) {

	case 0:
			Spieler1->Attack();
			sh.playSound("Swordswing");
	
		break;//Spieler1->attack.setattack();
	case 1:	/*isdefending*/ break;

	case 2: /*slide = true*/; break;
	case 3: printf("schwert leuchten\n"); break;

	case 4: break; //feuerring

	case 5: printf("feuerschwerrt");	break;

		//fireball
	case 6:

		if (Spieler1->CanSpell())
		{
			if (Spieler1->HaveEnoughMana(5))
			{
				eh.PopFireBullet(pp.x, pp.y, Spieler1->getAngleToTarget(game.window.mapPixelToCoords(mousepos)), Spieler1->attributs.getiq(), Spieler1->returnplayer_direction() - 1);
				sh.playSound("Fireballsound");
				Spieler1->ResetCastTimer();
				Spieler1->attributs.drainMana(5);
			}
			else
			{
				sh.playSound("nomana2");
			}

		}

		break;

	case 7: printf("feuersaeule\n"); break;
	
	case 8:
		

		if (Spieler1->CanSpell())
		{

			if (Spieler1->HaveEnoughMana(5))
			{
				eh.PopMagickBullet(pp.x+15, pp.y+20, Spieler1->getAngleToTarget(game.window.mapPixelToCoords(mousepos)), Spieler1->attributs.getiq());
				sh.playSound("Snowballsound");
				Spieler1->ResetCastTimer();
				Spieler1->attributs.drainMana(5);

			}else
			{
			sh.playSound("nomana1");
			}

		}
		


	
		break;

			//iceshild
	case 9:break;

		//iceorb
	case 10: 
	
		if (Spieler1->CanSpell())
		{

			if (Spieler1->HaveEnoughMana(20))
			{
				eh.popIceOrb(Spieler1->attributs.getiq(), Spieler1->getPosition().x, Spieler1->getPosition().y);
				Spieler1->ResetCastTimer();
				Spieler1->attributs.drainMana(20);
			}
			else
			{
				sh.playSound("nomana1");
			}
		}

		
		break;
	case 11:

		//achtung blizzard schwierig, pointer und so
		if (ptr_magickblizzard == nullptr) {
			mb = new MagickBlizzard();
			ptr_magickblizzard = mb;
			eh.pop_entity(mb);
			Spieler1->attributs.drainMana(2);

		} break;

	case 12: printf("kommt noch - heilen\n"); break;
	case 13:
		if (Spieler1->CanSpell())
		{

			if (Spieler1->HaveEnoughMana(10))
			{
				eh.PopRaven(Spieler1->getPosition().x, Spieler1->getPosition().y);
				Spieler1->ResetCastTimer();
				Spieler1->attributs.drainMana(10);
			}
			else
			{
				sh.playSound("nomana1");
			}
		} break;
	case 14: printf("kommt noch - psyball\n");break;
	case 15:break;
	default: break;

	}

	if (Spieler1->attributs.isalive()) {  }
	else {
		//map
		printf("spisler sollte tot sein \n\n");
		TileMapPainter.setBlack();
		TextManager.popTextbox("                       Game Over", sf::Vector2f(600, 450));
		//Spieler1->attack.set_invisible();
	}

		
}

void Main_Game::handlePlayerInput(Game & game)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		//Spieler1->move(0.f,-1.f,dt);

	}


}

