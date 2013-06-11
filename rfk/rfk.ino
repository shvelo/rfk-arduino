/* 
 * robotfindskitten v1600000.666 (Arduino) source code.
 *
 * Copyright (C) 1997,1999 Leonard Richardson leonardr@segfault.org
 *
 * Arduino Port by Nick Shvelidze 2013, shveloo@gmail.com
 * AVR Port by Daniel Beer 2003 (C) 2003, dbb28@cornell.edu
*/

#define BAUD_RATE 19200 //desired baud rate

// Controls:
#define PIN_UP 2 // up - digital pin 2
#define PIN_DOWN 3 // down - digital pin 3
#define PIN_LEFT 4 // left - digital pin 4
#define PIN_RIGHT 5 // right - digital pin 5

#define EMPTY 0
#define ROBOT 1
#define KITTEN 2
#define MESSAGES 150
#define NUM_BOGUS 10


void instructions(void);
void draw_robot(void);
void draw_kitten(void);
uint8_t PlayGame(void);
uint8_t random8(void);
char* inttostr(uint8_t input);
void SetupNewGame(void);
void clrscr(void);
void textcolor(uint8_t color);
uint8_t getspaceat(uint8_t x, uint8_t y, uint8_t numtocheck);
void gotoxy(uint8_t x, uint8_t y);

char output[4];
uint8_t counter;

uint8_t robotx, roboty;
uint8_t kittenx, kitteny, kittencolor;
uint8_t bogusx[NUM_BOGUS], bogusy[NUM_BOGUS], boguscolor[NUM_BOGUS];
uint8_t bogus_messages[NUM_BOGUS];
unsigned char boguschar[NUM_BOGUS];
unsigned char kittenchar;
uint8_t seed = 1;

const char message1[] PROGMEM = "\"I pity the fool who mistakes me for kitten!\", sez Mr. T.";
const char message2[] PROGMEM = "That's just an old tin can.";
const char message3[] PROGMEM = "It's an altar to the horse god."; 
const char message4[] PROGMEM = "A box of dancing mechanical pencils. They dance! They sing!";
const char message5[] PROGMEM = "It's an old Duke Ellington record.";
const char message6[] PROGMEM = "A box of fumigation pellets.";
const char message7[] PROGMEM = "A digital clock. It's stuck at 2:17 PM.";
const char message8[] PROGMEM = "That's just a charred human corpse.";
const char message9[] PROGMEM = "I don't know what that is, but it's not kitten.";
const char message10[] PROGMEM = "An empty shopping bag. Paper or plastic?";
const char message11[] PROGMEM = "Could it be... a big ugly bowling trophy?";
const char message12[] PROGMEM = "A coat hanger hovers in thin air. Odd.";
const char message13[] PROGMEM = "Not kitten, just a packet of Kool-Aid(tm).";
const char message14[] PROGMEM = "A freshly-baked pumpkin pie.";
const char message15[] PROGMEM = "A lone, forgotten comma, sits here, sobbing.";
const char message16[] PROGMEM = "ONE HUNDRED THOUSAND CARPET FIBERS!";
const char message17[] PROGMEM = "It's Richard Nixon's nose!";
const char message18[] PROGMEM = "It's Lucy Ricardo. \"Aaaah, Ricky!\"; she says.";
const char message19[] PROGMEM = "You stumble upon Bill Gates' stand-up act.";
const char message20[] PROGMEM = "Just an autographed copy of the Kama Sutra.";
const char message21[] PROGMEM = "It's the Will Rogers Highway. Who was Will Rogers, anyway?";
const char message22[] PROGMEM = "It's another robot, more advanced in design than you but strangely immobile.";
const char message23[] PROGMEM = "Leonard Richardson is here, asking people to lick him.";
const char message24[] PROGMEM = "It's a stupid mask, fashioned after a beagle.";
const char message25[] PROGMEM = "Your State Farm Insurance(tm) representative!";
const char message26[] PROGMEM = "It's the local draft board.";
const char message27[] PROGMEM = "Seven 1/4\" screws and a piece of plastic.";
const char message28[] PROGMEM = "An 80286 machine.";
const char message29[] PROGMEM = "One of those stupid \"Homes of the Stars\" maps.";
const char message30[] PROGMEM = "A signpost saying \"TO KITTEN\". It points in no particular direction.";
const char message31[] PROGMEM = "A hammock stretched between a tree and a volleyball pole.";
const char message32[] PROGMEM = "A Texas Instruments of Destruction calculator.";
const char message33[] PROGMEM = "It's a dark, amphorous blob of matter.";
const char message34[] PROGMEM = "Just a pincushion.";
const char message35[] PROGMEM = "It's a mighty zombie talking about some love and prosperity.";
const char message36[] PROGMEM = "\"Dear robot, you have been personally selected to recieve this Visa card...\"";
const char message37[] PROGMEM = "It's just an object.";
const char message38[] PROGMEM = "A mere collection of pixels.";
const char message39[] PROGMEM = "A badly dented high-hat cymbal lies on its side here.";
const char message40[] PROGMEM = "A marijuana brownie.";
const char message41[] PROGMEM = "A plush Chewbacca.";
const char message42[] PROGMEM = "Daily hunger conditioner from Australasia";
const char message43[] PROGMEM = "Just some stuff.";
const char message44[] PROGMEM = "Why are you touching this when you should be finding kitten?";
const char message45[] PROGMEM = "A glorious fan of peacock feathers.";
const char message46[] PROGMEM = "It's some compromising photos of Babar the Elephant.";
const char message47[] PROGMEM = "A copy of the Weekly World News. Watch out for the chambered nautilus!";
const char message48[] PROGMEM = "It's the proverbial wet blanket.";
const char message49[] PROGMEM = "A \"Get Out of Jail Free\" card.";
const char message50[] PROGMEM = "An incredibly expensive \"Mad About You\" collector plate.";
const char message51[] PROGMEM = "Paul Moyer's necktie.";
const char message52[] PROGMEM = "A haircut and a real job. Now you know where to get one!";
const char message53[] PROGMEM = "An automated robot-hater. It frowns disapprovingly at you.";
const char message54[] PROGMEM = "An automated robot-liker. It smiles at you.";
const char message55[] PROGMEM = "It's a black hole. Don't fall in!";
const char message56[] PROGMEM = "Just a big brick wall.";
const char message57[] PROGMEM = "You found kitten! No, just kidding.";
const char message58[] PROGMEM = "Heart of Darkness brand pistachio nuts.";
const char message59[] PROGMEM = "A smoking branding iron shaped like a 24-pin connector.";
const char message60[] PROGMEM = "It's a Java applet.";
const char message61[] PROGMEM = "An abandoned used-car lot.";
const char message62[] PROGMEM = "A shameless plug for Crummy - The Site: http://crummy.home.ml.org";
const char message63[] PROGMEM = "A shameless plug for Nerth Pork: http://www.northpark.edu/~ppeters/nerth_pork/";
const char message64[] PROGMEM = "A can of Spam Lite.";
const char message65[] PROGMEM = "This is another fine mess you've gotten us into, Stanley.";
const char message66[] PROGMEM = "It's scenery for \"Waiting for Godot\".";
const char message67[] PROGMEM = "A grain elevator towers high above you.";
const char message68[] PROGMEM = "A Mentos wrapper.";
const char message69[] PROGMEM = "It's the constellation Pisces.";
const char message70[] PROGMEM = "It's a fly on the wall. Hi, fly!";
const char message71[] PROGMEM = "This kind of looks like kitten, but it's not.";
const char message72[] PROGMEM = "It's a banana! Oh, joy!";
const char message73[] PROGMEM = "A helicopter has crashed here.";
const char message74[] PROGMEM = "Carlos Tarango stands here, doing his best impression of Pat Smear.";
const char message75[] PROGMEM = "A patch of mushrooms grows here.";
const char message76[] PROGMEM = "A patch of grape jelly grows here.";
const char message77[] PROGMEM = "A spindle, and a grindle, and a bucka-wacka-woom!";
const char message78[] PROGMEM = "A geyser sprays water high into the air.";
const char message79[] PROGMEM = "A toenail? What good is a toenail?";
const char message80[] PROGMEM = "You've found the fish! Not that it does you much good in this game.";
const char message81[] PROGMEM = "A Buttertonsils bar.";
const char message82[] PROGMEM = "One of the few remaining discoes.";
const char message83[] PROGMEM = "Ah, the uniform of a Revolutionary-eta minuteman.";
const char message84[] PROGMEM = "A punch bowl, filled with punch and lemon slices.";
const char message85[] PROGMEM = "It's nothing but a G-thang, baby.";
const char message86[] PROGMEM = "IT'S ALIVE! AH HA HA HA HA!";
const char message87[] PROGMEM = "This was no boating accident!";
const char message88[] PROGMEM = "Wait! This isn't the poker chip! You've been tricked! DAMN YOU, MENDEZ!";
const char message89[] PROGMEM = "A livery stable! Get your livery!";
const char message90[] PROGMEM = "It's a perpetual immobility machine.";
const char message91[] PROGMEM = "\"On this spot in 1962, Henry Winkler was sick.\"";
const char message92[] PROGMEM = "There's nothing here; it's just an optical illusion.";
const char message93[] PROGMEM = "The World's Biggest Motzah Ball!";
const char message94[] PROGMEM = "A tribe of cannibals lives here. They eat Malt-O-Meal for breakfast, you know.";
const char message95[] PROGMEM = "This appears to be a large stack of trashy romance novels.";
const char message96[] PROGMEM = "Look out! Exclamation points!";
const char message97[] PROGMEM = "A herd of wild coffee mugs slumbers here.";
const char message98[] PROGMEM = "It's a limbo bar! How low can you go?";
const char message99[] PROGMEM = "It's the horizon. Now THAT'S weird.";
const char message100[] PROGMEM = "A vase full of artificial flowers is stuck to the floor here.";
const char message101[] PROGMEM = "A large snake bars your way.";
const char message102[] PROGMEM = "A pair of saloon-style doors swing slowly back and forth here.";
const char message103[] PROGMEM = "It's an ordinary bust of Beethoven... but why is it painted green?";
const char message104[] PROGMEM = "It's TV's lovable wisecracking Crow! \"Bite me!\"; he says.";
const char message105[] PROGMEM = "Hey, look, it's war. What is it good for? Absolutely nothing. Say it again.";
const char message106[] PROGMEM = "It's the amazing self-referential thing that's not kitten.";
const char message107[] PROGMEM = "A flamboyant feather boa. Now you can dress up like Carol Channing!";
const char message108[] PROGMEM = "\"Sure hope we get some rain soon,\" says Farmer Joe.";
const char message109[] PROGMEM = "\"How in heck can I wash my neck if it ain't gonna rain no more?\" asks Farmer Al.";
const char message110[] PROGMEM = "\"Topsoil's all gone, ma,\" weeps Lil' Greg.";
const char message111[] PROGMEM = "This is a large brown bear. Oddly enough, it's currently peeing in the woods.";
const char message112[] PROGMEM = "A team of arctic explorers is camped here.";
const char message113[] PROGMEM = "This object here appears to be Louis Farrakhan's bow tie.";
const char message114[] PROGMEM = "This is the world-famous Chain of Jockstraps.";
const char message115[] PROGMEM = "A trash compactor, compacting away.";
const char message116[] PROGMEM = "This toaster strudel is riddled with bullet holes!";
const char message117[] PROGMEM = "It's a hologram of a crashed helicopter.";
const char message118[] PROGMEM = "This is a television. On screen you see a robot strangely similar to yourself.";
const char message119[] PROGMEM = "This balogna has a first name, it's R-A-N-C-I-D.";
const char message120[] PROGMEM = "A salmon hatchery? Look again. It's merely a single salmon.";
const char message121[] PROGMEM = "It's a rim shot. Ba-da-boom!";
const char message122[] PROGMEM = "It's creepy and it's kooky, mysterious and spooky. It's also somewhat ooky.";
const char message123[] PROGMEM = "This is an anagram.";
const char message124[] PROGMEM = "This object is like an analogy.";
const char message125[] PROGMEM = "It's a symbol. You see in it a model for all symbols everywhere.";
const char message126[] PROGMEM = "The object pushes back at you.";
const char message127[] PROGMEM = "A traffic signal. It appears to have been recently terrorized.";
const char message128[] PROGMEM = "\"There is no kitten!\" cackles the old crone. You are shocked by her blasphemy.";
const char message129[] PROGMEM = "This is a Lagrange point. Don't come too close now.";
const char message130[] PROGMEM = "The dirty old tramp bemoans the loss of his harmonica.";
const char message131[] PROGMEM = "Look, it's Fanny the Irishman!";
const char message132[] PROGMEM = "What in blazes is this?";
const char message133[] PROGMEM = "It's the instruction manual for a previous version of this game.";
const char message134[] PROGMEM = "A brain cell. Oddly enough, it seems to be functioning.";
const char message135[] PROGMEM = "Tea and/or crumpets.";
const char message136[] PROGMEM = "This jukebox has nothing but Cliff Richards albums in it.";
const char message137[] PROGMEM = "It's a Quaker Oatmeal tube, converted into a drum.";
const char message138[] PROGMEM = "This is a remote control. Being a robot, you keep a wide berth.";
const char message139[] PROGMEM = "It's a roll of industrial-strength copper wire.";
const char message140[] PROGMEM = "Oh boy! Grub! Er, grubs.";
const char message141[] PROGMEM = "A puddle of mud, where the mudskippers play.";
const char message142[] PROGMEM = "Plenty of nothing.";
const char message143[] PROGMEM = "Look at that, it's the Crudmobile.";
const char message144[] PROGMEM = "Just Walter Mattheau and Jack Lemmon.";
const char message145[] PROGMEM = "Two crepes, two crepes in a box.";
const char message146[] PROGMEM = "An autographed copy of \"Primary Colors\"; by Anonymous.";
const char message147[] PROGMEM = "Another rabbit? That's three today!";
const char message148[] PROGMEM = "It's a segmentation fault. Core dumped, by the way.";
const char message149[] PROGMEM = "A historical marker showing the actual location of /dev/null.";
const char message150[] PROGMEM = "Thar's Mobius Dick, the convoluted whale. Arrr!";

const char* messages[] = {
  message1, message2, message3, message4, message5, message6, message7, message8, message9, message10,
  message11, message12, message13, message14, message15, message16, message17, message18, message19, message20,
  message21, message22, message23, message24, message25, message26, message27, message28, message29, message30,
  message31, message32, message33, message34, message35, message36, message37, message38, message39, message40,
  message41, message42, message43, message44, message45, message46, message47, message48, message49, message50,
  message51, message52, message53, message54, message55, message56, message57, message58, message59, message60,
  message61, message62, message63, message64, message65, message66, message67, message68, message69, message70,
  message71, message72, message73, message74, message75, message76, message77, message78, message79, message80,
  message81, message82, message83, message84, message85, message86, message87, message88, message89, message90,
  message91, message92, message93, message94, message95, message96, message97, message98, message99, message100,
  message101, message102, message103, message104, message105, message106, message107, message108, message109, message110,
  message111, message112, message113, message114, message115, message116, message117, message118, message119, message120,
  message121, message122, message123, message124, message125, message126, message127, message128, message129, message130,
  message131, message132, message133, message134, message135, message136, message137, message138, message139, message140,
  message141, message142, message143, message144, message145, message146, message147, message148, message149, message150
};

char readButtons() {
  if(digitalRead(PIN_UP) == HIGH) return 'w';
  else if(digitalRead(PIN_DOWN) == HIGH) return 's';
  else if(digitalRead(PIN_LEFT) == HIGH) return 'a';
  else if(digitalRead(PIN_RIGHT) == HIGH) return 'd';
  else return 0;
}

char get_input() {
  char b;
  
  while(Serial.available() == 0 && (b = readButtons()) == 0);
  
  if(Serial.available() > 0) b = Serial.read();
  
  return b;
}

void uart_puts_P(char str[]) {
  Serial.write(str);
}

void uart_puts_p(const char *progmem_s ) {
  register char c;
  while ( (c = pgm_read_byte(progmem_s++)) ) 
    uart_putc(c);
}

void uart_puts(char str[]) {
  Serial.write(str);
}

void uart_putc(char ch) {
  Serial.write(ch);
}

void _delay_loop_2(int t) {
  delay(t / 400);
}

char uart_getc() {
  while(Serial.available() == 0);
  char c = Serial.read();
  return c;
}

void setup()
{
  pinMode(PIN_UP, INPUT);
  pinMode(PIN_DOWN, INPUT);
  pinMode(PIN_LEFT, INPUT);
  pinMode(PIN_RIGHT, INPUT);
  digitalWrite(PIN_UP, HIGH);
  digitalWrite(PIN_LEFT, HIGH);
  digitalWrite(PIN_RIGHT, HIGH);
  digitalWrite(PIN_DOWN, HIGH);
  
  Serial.begin(BAUD_RATE);
  
  // Get random seed
  for (uint8_t a = 0; a < 2; a++)
  {
    unsigned char input = analogRead(A0);
    seed = seed + input;
  }
  
  clrscr();
	
  instructions();
}

void loop() {
  clrscr();
  SetupNewGame();
  uint8_t score = PlayGame();
  gotoxy(27,12);
  uart_puts_P("Press any key to continue");
  get_input();
}

void SetupNewGame(void)
{
	static uint8_t used_messages[MESSAGES];

	//
	//Now we have the filling in of the various arrays.
	//

	//Create an array to ensure we don't get duplicate messages.
	for (counter = 0; counter < MESSAGES; counter++)
	{
		used_messages[counter] = 0;
	}

	//
	//Now we initialize the various game objects.
	//
	//Assign a position to the player.
	robotx = (uint8_t)(random8() % 79+1);
	roboty = (uint8_t)(random8() % 21+4);

	//Assign the kitten a unique position.
	do
	{
		kittenx = (uint8_t)(random8() % 79+1);
		kitteny = (uint8_t)(random8() % 21+4);
	} while ((kittenx == robotx)&&(kitteny == roboty));

	//Assign the kitten a character and a color.
	do
	{
		kittenchar = random8() % 222 + 33;
	} while (kittenchar == '#');
	kittencolor = (uint8_t)(random8() % 7 + 1);

	//Now, initialize non-kitten objects.
	for (counter = 0; counter < NUM_BOGUS; counter++)
	{
		uint8_t newx, newy;
		//Assign a unique position.
		do
		{
			newx = (uint8_t)(random8() % 79+1);
			newy = (uint8_t)(random8() % 21+4);
		} while (getspaceat(newx,newy,counter));
		bogusx[counter] = newx;
		bogusy[counter] = newy;
		
		//Assign a character.
		do
		{
			boguschar[counter] = random8() % 222 + 33;
		} while (boguschar[counter] == '#' || boguschar[counter] == ' ' || boguschar[counter] == (unsigned char)7);
		boguscolor[counter] = (uint8_t)(random8() % 7 + 1);

		//Assign a unique message.
		uint8_t index = 0;
		do
		{
			index = (uint8_t)(random8() % MESSAGES);
		} while (used_messages[index] != 0);
		bogus_messages[counter] = index;
		used_messages[index] = 1;
	}
}

uint8_t PlayGame(void)
{
	uint8_t moves = 0;
	
	//Put stuff on the screen.
	textcolor(7);
	gotoxy(1,1);
	uart_puts_P("robotfindskitten v1600000.666 (AVR)");
	gotoxy(kittenx,kitteny);
	draw_kitten();
	
	for (counter = 0; counter < NUM_BOGUS; counter++)
	{
		gotoxy(bogusx[counter],bogusy[counter]);
		textcolor(boguscolor[counter]);
		uart_putc(boguschar[counter]);
	}

	gotoxy(robotx,roboty);
	draw_robot();
	uint8_t old_x = robotx;
	uint8_t old_y = roboty;

	//
	//Now the fun begins.
	//
	unsigned char input = get_input();
        
	uint8_t gameover = 0;
	
	while (!gameover) {
                
		input = get_input();
	
		uint8_t check_x = robotx;
		uint8_t check_y = roboty;
		
		if (input == 'w') check_y--;
		else if (input == 's') check_y++;
		else if (input == 'a') check_x--;
		else if (input == 'd') check_x++;
		else if (input == 0);
		else
		{
			gotoxy(1,2);
			textcolor(7);
			uart_puts_P("\e[K");
			uart_puts_P("Invalid command: Use W, A, S, D");	
		}
		
		//Check for going off the edge of the screen.
		if (check_y < 4 || check_y > 24 || check_x < 1 || check_x > 79);
		else if (getspaceat(check_x,check_y,NUM_BOGUS) != EMPTY)	//Check for collision
		{
			switch (getspaceat(check_x, check_y,NUM_BOGUS))
			{
				case ROBOT:
					//We didn't move.
					break;
				case KITTEN: //Found it!
					moves ++;
				
					gotoxy(1,2);
					uart_puts_P("\e[K");
					
					//The grand cinema scene.
					for (int counter = 0; counter <=3; counter++)
					{
						gotoxy(55+counter-1,2);
						uart_putc(' ');
						gotoxy(62-counter+1,2);
						uart_putc(' ');
						gotoxy(55+counter,2);
						if (input == 'a' || input == 's')
							draw_kitten();
						else
							draw_robot();
						gotoxy(62-counter,2);
						if (input == 'a' || input == 's')
							draw_robot();
						else
							draw_kitten();
						for (int a = 0; a< 10; a++)
							_delay_loop_2 (30000);
					}
					//They're in love!
					gotoxy(58,1);
					textcolor(1);
					uart_putc((unsigned char)3);
					uart_putc((unsigned char)3);
					gotoxy(1,2);
					for (int a = 0; a< 20; a++)
						_delay_loop_2 (30000);
					textcolor(7);
					uart_puts_P("You found kitten! Way to go, robot!\n");

					gameover = 1;
					break;
				default:
					moves ++;
					
					gotoxy(1,2);
					uart_puts_P("\e[K");
					char* message = (char*)messages[bogus_messages[getspaceat(check_x,check_y,NUM_BOGUS)-3]];
					uart_puts_p(message);
					break;
			}

		}
		else
		{
			moves ++;
			
			//Otherwise, move the robot.
			robotx = check_x;
			roboty = check_y;
		}
		
		//Redraw robot, where avaliable
		if (!(old_x == robotx && old_y == roboty))
		{
			gotoxy(old_x,old_y);
			uart_putc(' ');
			gotoxy(robotx,roboty);
			draw_robot();
			old_x = robotx;
			old_y = roboty;
		}
		
		gotoxy(76,1);
		uart_puts(inttostr(moves));
	}
	
	return moves;
}

void instructions()
{
	gotoxy(1,1);
	uart_puts_P ("robotfindskitten v1600000.666 (AVR)\n\r");
	uart_puts_P ("By the illustrious Leonard Richardson (C) 1997\n\r");
	uart_puts_P ("AVR Port by Daniel Beer (C) 2003\n\r\n\r");
	uart_puts_P ("   In this game, you are robot (");
	draw_robot();
	textcolor(7);
	uart_puts_P ("). Your job is to find kitten. This task\n\r");
	uart_puts_P ("is complicated by the existance of various things which are not kitten.\n\r");
	uart_puts_P ("Robot must touch items to determine if they are kitten or not. The game\n\r");
	uart_puts_P ("ends when robotfindskitten. See the documentation for more information.\n\r\n\r");
	uart_puts_P ("\n\r\n\r");
	uart_puts_P ("   Press any key to start.\n\r");
	get_input();
}

void draw_robot() //Draws robot at current position
{
	textcolor(7);
	bgcolor(1);
	uart_putc('#');
	bgcolor(0);
}

void draw_kitten() //Draws kitten at current position
{
	textcolor(kittencolor);
	uart_putc(kittenchar);
}


uint8_t random8(void)
{
	uint8_t newbit;

	newbit=((seed>> 7)&1) ^
		   ((seed>> 1)&1) ^
		   ((seed    )&1);
	
	seed = (seed<<1)|newbit;

	return seed;
}

char* inttostr(uint8_t input)
{
	char onesdigit = (char)((input % 10)+48);
	
	if (input > 99)
	{
		output[0] = (char)((input / 100)+48);
		output[1] = (char)(((input % 100) / 10)+48);
		output[2] = onesdigit;
		output[3] = '\0';
	}
	else if (input > 9) 
	{
		output[0] = (char)((input / 10)+48);
		output[1] = onesdigit;
		output[2] = '\0';
	}
	else
	{
		output[0] = onesdigit;
		output[1] = '\0';
	}
	
	return &output[0];
}

void gotoxy(uint8_t x, uint8_t y)
{
	uart_puts_P("\e[");
	uart_puts(inttostr(y));
	uart_putc(';');
	uart_puts(inttostr(x));
	uart_putc('H');
}

void clrscr(void)
{
	uart_puts_P("\e[40m\e[2J\e[1m");
}

void textcolor(uint8_t color)
{
	uart_puts_P("\e[3");
	uart_putc(color + 48);
	uart_putc('m');
}

void bgcolor(uint8_t color)
{
	uart_puts_P("\e[4");
	uart_putc(color + 48);
	uart_putc('m');
}

uint8_t getspaceat(uint8_t x, uint8_t y, uint8_t numtocheck)
{
	if ((robotx == x)&&(roboty == y)) return ROBOT;
	else if ((kittenx == x)&&(kitteny == y)) return KITTEN;
	else for (int counter = 0; counter < numtocheck; counter ++)
			if ((bogusx[counter] == x)&&(bogusy[counter] == y)) return counter+3;
	
	return EMPTY;
}
