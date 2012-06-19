--Pickomino Lua
print("Pickomino Lua!");
--starting sound
NUMBEROFDICE=8;
NUMBEROFPLAYERS=2;

GAPLOCKED=0
GAPOBJECTPHYSICAL=1

GENABLED=0
GTAKEN=1

FIRSTBUTTON=21;
LASTBUTTON=36;
--LASTBUTTON=23

gameended=false;
dicesrolling=false;
tilepicked=false;
dicepicked=false

--scorestring="";

function tilepointvalues(Tile)
	if Tile=="21" then return 1
	end
	if Tile=="22" then return 1
	end
	if Tile=="23" then return 1
	end
	if Tile=="24" then return 1
	end
	if Tile=="25" then return 2
	end
	if Tile=="26" then return 2
	end
	if Tile=="27" then return 2
	end
	if Tile=="28" then return 2
	end
	if Tile=="29" then return 3
	end
	if Tile=="30" then return 3
	end
	if Tile=="31" then return 3
	end
	if Tile=="32" then return 3
	end
	if Tile=="33" then return 4
	end
	if Tile=="34" then return 4
	end
	if Tile=="35" then return 4
	end
	if Tile=="36" then return 4
	end
	return 0;
end;

function translateresult(WhatIsRolled)
	if WhatIsRolled==1 then return 3
	end
	if WhatIsRolled==2 then return 2
	end
	if WhatIsRolled==3 then return 4
	end
	if WhatIsRolled==4 then return 6
	end
	if WhatIsRolled==5 then return 1
	end
	if WhatIsRolled==6 then return 5
	end
	return 0;
end;

function resulttostring(Roll)
	if Roll==1 then return "1"
	end
	if Roll==2 then return "2"
	end
	if Roll==3 then return "3"
	end
	if Roll==4 then return "4"
	end
	if Roll==5 then return "5"
	end
	if Roll==6 then return "W"
	end
	return "0";
end;

function gametileposition(tilenumber)--sets the position of a proper tile
	return (40+35*(tilenumber-21)),10, (40+35*(tilenumber-20)),90;
end;
function gamedicetileposition(tilenumber)--sets the position of a game dice tile
	return (200+50*tilenumber),400, (250+50*tilenumber),450;
end;

function loadbasictiles(Start, End)
	for i=Start, End do
		a, b, c, d=gametileposition(i)
		createbuttonwithgraphics("textures/"..i..".jpg", ""..i, a, b, c, d, true, false);
	end;
end;
function loaddicetiles()
	for i=1, 6 do
		a, b, c, d=gamedicetileposition(i)
		createbuttonwithgraphics("textures/"..i..".jpg", ""..i, a, b, c, d, true, false);
	end;
end;

function setdice(i)--function for setting up a dice
	setgameobject(i, 0, 3+5*i, 0, getfloatbetween(-9, 9), getfloatbetween(-9, 9), getfloatbetween(-9, 9), getfloatbetween(-9, 9), getfloatbetween(-9, 9), getfloatbetween(-9, 9));
end;

function rolldice()
	playsound(1);
	for i=0, getgomsize()-1 do
		if getgomhandle(i, GAPOBJECTPHYSICAL)==true then
			if getgomhandle(i, GAPLOCKED)==false then
				setdice(i);
			end;
		end;
	end;
	dicesrolling=true;
end;

function generatedicestring()--function to generate a string of which dice are rolled
	dicestring="";
	for i=0, getgomsize()-1 do
		if getgomhandle(i, GAPOBJECTPHYSICAL)==true then
			if getgomhandle(i, GAPLOCKED)==false then
				dicestring=dicestring..resulttostring(translateresult(whatisrolled(i)))
			end;
		end;
	end;
	return dicestring;
end;

function generatescorestring()
	return "scorestr";
end;

function checkforvaliddice()
	dicerolled={};
	for i=1, 6 do
		dicerolled[i]=false;
	end;
	for i=0, getgomsize()-1 do
		if getgomhandle(i, GAPOBJECTPHYSICAL)==true then
			if getgomhandle(i, GAPLOCKED)==false then
				dicerolled[translateresult(whatisrolled(i))]=true;
			end;
		end;
	end;
	for i=1, 6 do
		if(getgbmhandle(""..i, GENABLED)==false) then
			dicerolled[i]=false;
		end;
	end;
	anwser=false;
	for i=1, 6 do
		anwser=anwser or dicerolled[i];
	end;
	return anwser;
end;

function countdiceresult()
	anwser=0;
	tmp=0;
	for i=0, getgomsize()-1 do
		if getgomhandle(i, GAPOBJECTPHYSICAL)==true then
			if getgomhandle(i, GAPLOCKED)==true then
				tmp=translateresult(whatisrolled(i));
				if tmp==6 then
					tmp=5;
				end;
				anwser=anwser+tmp;
			end;
		end;
	end;
	return anwser;
end;

function setscorestring()
	scorestring="Player "..(getcurrentplayernumber()+1).."\nCount "..countdiceresult();
end;

function startgame()--function that will be executed at the start of the game
	--for i=0, NUMBEROFDICE-1 do
	--setdice(i);
	--end;
	rolldice();
	print("Game starting, good luck!");
end;
function countplayerscore(Number)
	score=0;
	tiles={getplayertiles(Number)};
	if (tiles~=nil) then
		for i in ipairs(tiles) do
			score=score+tilepointvalues(tiles[i]);
		end;
	end;
	return score;
end;

function printscores()
	scores="";
	for i=0, NUMBEROFPLAYERS-1 do
		scores=scores..countplayerscore(i).." ";
	end;
	return scores;
end;

function whowon()
--TODO: pick proper player in case of a tie
	topscore=0;
	topplayer=0;
	tmpscore=0;
	for i=0, NUMBEROFPLAYERS-1 do
		tmpscore=countplayerscore(i);
		if (tmpscore>topscore) then
			toppplayer=i;
		end;
	end;
	
	return topplayer+1;
end;

function failedmove()

	tile=getplayertile(getcurrentplayernumber());
	if tile~="" then
		popplayertile(getcurrentplayernumber(), tile);
		resetbutton(tile);
		setgbmhandle(tile, GENABLED, true);
		setgbmhandle(tile, GTAKEN, false);
		tile2=getplayertile(getcurrentplayernumber());
		if tile2~="" then
			setgbmhandle(tile2, GENABLED, true);
			setbuttoncolour(tile2, 255, 255, 255, 255);--resets the colour of player's top tile
		end;
	end;
	tilecleared=false;
	for i=LASTBUTTON, FIRSTBUTTON, -1 do
		if tilecleared==false then
			if ((getgbmhandle(""..i, GENABLED)==true) and (getgbmhandle(""..i, GTAKEN)==false)) then
				setgbmhandle(""..i, GENABLED, false);
				setbuttoncolour(""..i, 255, 150, 150, 150);
				tilecleared=true;
			end;
		end;
	end;
end;

function simulationend()--function that will be executed after ODE is done simulating
	--print("simulationend");
	if dicesrolling==true then
		dicesrolling=false;
		dicestring=generatedicestring();
		
		if checkforvaliddice()==true then
			print("Valid moves");
		else
			print("No valid moves");
			failedmove();
			tilepicked=true;
			print("Player number "..(getcurrentplayernumber()+1).."\n");
			dicesrolling=false;
			if checkforgameend()==true then
				endstr="Player "..whowon().." won!\nPoints: "..printscores();
			end;
		end;
		
		print (dicestring);
	end;
end;


function checkforgameend()
	--print("checkforgameend()");
	endofgame=true;
	
	for i=FIRSTBUTTON, LASTBUTTON do
		if(getgbmhandle(""..i, GENABLED)==true) then
			if(getgbmhandle(""..i, GTAKEN)==false) then
				endofgame=false;
			end;
		end;
	end;
	
	return endofgame;
end;

function canbuttonbepicked(Number)
	anwser=false;
	for i=0, getgomsize()-1 do
		if getgomhandle(i, GAPOBJECTPHYSICAL)==true then
			if getgomhandle(i, GAPLOCKED)==false then
				anwser=anwser or (translateresult(whatisrolled(i))==Number);
				--print("canbuttonbepicked"..i.."==");
				--print(anwser);
			end;
		end;
	end;
	return anwser;
end;

function lockdice(Number)
	for i=0, getgomsize()-1 do
		if getgomhandle(i, GAPOBJECTPHYSICAL)==true then
			if translateresult(whatisrolled(i))==Number then
				setgomhandle(i, GAPLOCKED, true);
				setgameobjectposition(i, 30, 100, 30);
			end;
		end;
	end;
end;

function unlockdice()
	for i=0, getgomsize()-1 do
		setgomhandle(i, GAPLOCKED, false);
	end;
end;

function stealtile(Name)
	for i=0, NUMBEROFPLAYERS-1 do
		if (doesplayerhavetile(i, Name)==true) then
			popplayertile(i, Name);
			tmp=getplayertile(i);
			if tmp~="" then
				setbuttoncolour(tmp, 255, 255, 255, 255);
				setgbmhandle(tmp, GENABLED, true);
			end;
		end;
	end;
end;

function taketile(Name)
	--print("taketile");
	tmp=getplayertile(getcurrentplayernumber());
	if tmp~="" then
		--print("tmp~=  ");
		setbuttoncolour(tmp, 0, 0, 0, 0);
		setgbmhandle(tmp, GENABLED, false);
	end;
	pushplayertile(getcurrentplayernumber(), Name);
	setgbmhandle(Name, GTAKEN, true);
	area={getplayersarea(getcurrentplayernumber())};
	setbuttonarea(Name, area[1], area[2], area[3], area[4]);
end;

function buttonfunction(Name)
	
	if getgbmhandle(Name, GENABLED)==true then
		if dicepicked==false then
			if (Name>"0" and Name<"7") then
				if(canbuttonbepicked(tonumber(Name))) then
					dicepicked=true;
					lockdice(tonumber(Name));
					setbuttoncolour(Name, 100, 255, 255, 255);
					setgbmhandle(Name, GENABLED, false);
				end;
			end;
		else
			if tilepicked==false then
				if getgbmhandle("6", GENABLED)==false then
					if (Name>=""..FIRSTBUTTON and Name<=""..LASTBUTTON) then
						if ((getgbmhandle(Name, GTAKEN)==false) or (Name==""..countdiceresult()))==true then
							if (doesplayerhavetile(getcurrentplayernumber(), Name)==false) then
								if (getgbmhandle(Name, GTAKEN)==true) then
									stealtile(Name);
								end;
								taketile(Name);
								tilepicked=true;
							end;
						end;
					end;
				end;
			end;
		end;
		if Name=="worm" then
			nextplayer(true);
		end;
		if dicepicked==true then
			if Name=="roll" then
				tilepicked=false;
				dicepicked=false;
				rolldice();
				setgbmhandle("roll", GENABLED, true);
			end;
		end;
	end;--if getgbmhandle(Name, GENABLED)==true then


end;

function printfunction()

	if(gameended) then
		printtext(endstr, 20,100,300,300, 255,255,255,255);
	else
		if(dicesrolling==false) then
			tmp=generatedicestring();
			anwser="Rolled:\n";
			anwser=anwser..string.sub(tmp, 1, 4).."\n"..string.sub(tmp, 5)
			printtext(anwser, 20,200,150,350, 255,255,255,255);
		end;
		setscorestring();
		--printtext(generatescorestring(), 20,100,300,300, 255,255,255,255);
		printtext(scorestring, 20,100,300,300, 255,255,255,255);
	end;

end;

function unlockbuttons()
	for i=1, 6 do
		resetbutton(""..i);
		setgbmhandle(""..i, GENABLED, true);
		setgbmhandle(""..i, GTAKEN, false);
	end;
	for i=FIRSTBUTTON, LASTBUTTON do
		resetbutton(""..i);
		setgbmhandle(""..i, GENABLED, true);
		setgbmhandle(""..i, GTAKEN, false);
	end;
	resetbutton("roll");
	setgbmhandle("roll", GENABLED, true);
	setgbmhandle("roll", GTAKEN, false);
	resetbutton("worm");
	setgbmhandle("worm", GENABLED, true);
	setgbmhandle("worm", GTAKEN, false);
end;

function unlockdicebuttons()
	for i=1, 6 do
		resetbutton(""..i);
		setgbmhandle(""..i, GENABLED, true);
		setgbmhandle(""..i, GTAKEN, false);
	end;
end;

function nextplayer(Reset)

	--dicepicked=false;
	dicepicked=true;
	-------tilepicked=true;
	tilepicked=false;
	unlockdice();
	
	if(Reset==true) then
		unlockbuttons();
		gameended=false;
		endstr="";
	else
		unlockdicebuttons();
	end;
	--rolldice();

	return pmnextplayer(Reset==true);


end;

function idlescript()--function that will be called each game loop
	if tilepicked==true then
	--print("tilepicked==true");
		if checkforgameend()==false then
			--print("checkforgameend()==false");
			nextplayer(false);
		else
			--print("!checkforgameend()==false");
			tilepicked=false;
			gameended=true;
			endstr="Player "..whowon().." won!\nPoints: "..printscores();
		end;
	
	
	
	end;--if tilepicked==true then



end;
function startingscript()--function that is executed at initialization of the game
	--creates the physical world
	addphysicalplane(0, 1, 0, 0);--ground
	addphysicalplane(-1, 0, 0, -10);
	addphysicalplane(1, -0, -0, -10);
	addphysicalplane(-0, 0, 1, -10);
	addphysicalplane(0, -0, -1, -10);

	setsound(0, "midis/22000_Candy-Floss.mid", true);--loads the music
	setsound(1, "midis/44060__Feegle__diceboard.wav", false);
	playsound(0);--plays the music

	--setdiceresultfunction("translateresult");--sets the function that translates the rotation of dice into what they rolled
	setwindowcaption("Pickomino!");--sets the name of the window
	createdice("textures/dice.x", NUMBEROFDICE, false, true);--loads 8 dice

	createbutton("roll", 100, 100, 500, 350, true);--creates a button without graphics

	--loading basic game tiles
	loadbasictiles(FIRSTBUTTON, LASTBUTTON);
	--loads the reset tile
	createbuttonwithgraphics("textures/worm.jpg", "worm", 50,350, 150,450, true, false);
	--creates dice tiles
	loaddicetiles();

	--sets up the camera
	setlookatcamera(0, 30, 0,		0, 0, 0);

	--creates the board model
	createmodel("textures/box.x", 7, -10, 10, false, false);

	--loads font
	loadfont("textures/curlz28.bmp");
	
	--adding players
	for i=0, NUMBEROFPLAYERS-1 do
		addplayer(550, 150+80*(i), 550+35, 150+80*(i+1));
	end;
	
	
	setstargamefunction("startgame");--sets up the function that will start the game
	setendofsimulationfunction("simulationend");--sets the function that will be run after ODE simulation
	setprintfunction("printfunction");
	setbuttonfunction("buttonfunction");
	setidlefunction("idlescript");
end


startingscript();


print("Script Loaded!");