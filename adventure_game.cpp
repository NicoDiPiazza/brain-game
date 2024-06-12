#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// ensures that the user provides a good input to the program
int get_good_int (){
    string user_str;
    int i; // i is an index/location in the string
    do{
        cin >> user_str; //reads characters until whitespace
        // for all characters in the string from 0 to length-1
        for(i=0; i< user_str.length(); i++){
            //error if a character is not between 0 and 5 on the ASCII chart
            if(user_str.at(i) < '0' || user_str.at(i) > '9'){
                cout << "Error. please enter a positive integer: ";
                break; // get out of the loop because we know there has been an error
                }
        }
    }while(i<user_str.length()); // i is equal to the length if not an error
    return stoi(user_str); //when string is an int, return string to integer
}

// ensures that the integer the user enters is within a specific range
int int_within_range(int min, int max, string message){
    int user_entry;
    // outputs whatever prompt message the programmer desires
    cout << message;

    //asks for an integer using the get_good_int function, then continues to ask untl the integer is between min and max
    do{
        user_entry = get_good_int();
        if(user_entry < min || user_entry > max){
            cout << "Please enter a number between " << min << " and " << max << " inclusive: ";
        }
    } while(user_entry < min || user_entry > max);
    return user_entry;

}

// generates solutions for the player to pick from
void solution_options(int player_location, string tools[], string solutions[], int &right_answer){
    right_answer = rand() % 3;
    int prev_rand_answer = -1;
    for(int i = 0; i < 3; i++){
        int random_answer = rand() % 8;
        while(random_answer == player_location || random_answer == prev_rand_answer){
            random_answer = rand() % 8;
        }
        solutions[i] = tools[random_answer];
        prev_rand_answer = random_answer;
    }
    solutions[right_answer] = tools[player_location];
}

// analyzes whether or not the answer the player chose was correct
int answer_analysis(int entry, int answer, int lives){
    if(entry == answer){
        cout << "That's right!" << endl;
        return 0;
    }
    else{
        cout << "That's not quite right..." << endl;
        lives--;
        cout << "You can only get " << lives << " more wrong." << endl;
        return 1;
    }
}

// CORE GAME MECHANIC: lets the player choose one of the presented solutions to the problem at hand
void player_choice(int player_location, string trivia[], string problems[], string tools[], int &lives, int &score){
    int right_answer;
    int player_choice;
    int change;
    string solutions[3];

    // this should print out the trivia for the player's current location, with a hint about the problem
    cout << trivia[player_location] << endl;
    cout << problems[player_location] << endl;
    solution_options(player_location, tools, solutions, right_answer);
    cout << "Fix the problem by using: " << solutions[0] << " | " << solutions[1] << " | " << solutions[2] << endl;

    player_choice = int_within_range(1, 3, "choose 1, 2, or 3: ") -1;
    change = answer_analysis(player_choice, right_answer, lives);
    lives = lives - change;
    score = score + (100 * (1-change));
}

// displays a minimap of the brain, with an x marking the player's position in the brain
void minimap_readout(int player_location, string map[], string insert_1, string insert_2){
    for(int i = 0; i<player_location; i++){
        cout << map[i] << endl;
    }
    cout << insert_1 << "\033[31m" << "X" << "\033[0m" << insert_2 << endl;
    for(int i = player_location +1; i<9; i++){
        cout << map[i] << endl;
    }
}

// the minimap being read from in minimap_readout
void minimap(int player_location){
    string map[9] = {"          ___..._..--------..._                    ", 
                    "        /      /                `-.                ",
                    "       |                           `-,            ",
                    "      (     |                        |           ",
                    "      {                             /           ",
                    "       `-,_                  _     }           ",
                    "            `----_=_______?    7)/            ",
                    "                           (  /              ",
                    "                            V               "};
    string location_inserts[16] = {"          ___..._..----", "---..._                    ", 
                                    "        / ", "    /                `-.                ",
                                    "       |        ", "                  `-,            ",
                                    "      (     |                     ", "  |           ",
                                    "      {            ", "                /           ",
                                    "       `-,_                 ", "_     }           ",
                                    "            `---", "_=_______?    7)/            ",
                                    "                           (", " /              "};
    minimap_readout(player_location, map, location_inserts[player_location*2], location_inserts[player_location *2 +1]);

}

// calculates the paths that the player can choose to take farther into the brain
void new_path(int player_location, string locations[]){
    if (player_location == 6){
        cout << "Move onward to the " << locations[7] << ". (press 1)" << endl;
    }
    else{
        cout << "One or two steps forward?" << endl;
        cout << "1: " << locations[player_location + 1] << "\n2: " << locations[player_location + 2] << "\n" << endl;
    }
}

// CORE GAME MECHANIC: lets the player move along the paths farther into the brain, choosing step size mostly
void player_move(int &player_location, string locations[]){
    int chosen_path;
    new_path(player_location, locations);

    chosen_path = int_within_range(1, 2, "1 or 2: ");
    player_location = player_location + chosen_path;
    if(player_location >7){
        player_location = 7;
    }
    cout << "Welcome to the " << locations[player_location] << endl;
    minimap(player_location);
}

// prints the title screen and logo
void title_screen(int &play_game){
    cout << "\n -------------------------------------------------------------------- \n \n";
    cout << "          ___..._..--------..._                                                " << endl;
    cout << "        /      /               `-.                                             " << endl;
    cout << "       |          REBUILD         `-,                                        " << endl;
    cout << "      (     |   A BONKERS           |                                       " << endl;
    cout << "      {           BRAIN            /                                        " << endl;
    cout << "       `-,_                  _    }                                           " << endl;
    cout << "            `----_=_______?    7)/                                              " << endl;
    cout << "                           (  /                                                " << endl;
    cout << "                            V                                                " << endl;
    cout << "Press any number, then press enter to continue: ";
    play_game = get_good_int();
}

// prints the intro text that gives context and instructions on how to play
void intro_text(int &play_game){
    cout << "Hi! In this game, you will be venturing into the brain of your patient. The patient read the necronomicon of Cthulhu, " << endl;
    cout << "and everything in their brain has broken as a result. Unfortunately, you are an engineer, and not a medical surgeon," << endl;
    cout << "so you will be repairing each portion of the brain with the appropriate part of a computer neural network." << endl;
    cout << "If you fail three times or finish without fixing at least four brain sections, the patient will lose their marbles!" << endl;
    cout << "There are eight sections, and the more you fix, the higher your score! Good luck!" << endl;
    cout << "\n Press any number, then press enter to continue: ";

    play_game = get_good_int();
    cout << "\n Welcome to the parietal lobe!" << endl;
    minimap(0);
}

// checks if the player is out of lives
void lost_lives(int lives, int &player_location){
    if(lives == 0){
        cout << "the patient went insane because you didn't save enough brain. ";
        cout << "Thanks for playing!" << endl;
        player_location = 100;
    }
}

// checks if the player has reached the bottom of the brain (they start at the top)
void player_too_far(int score, int &player_location){
    if(score >= 400){
        cout << "You won! "; 
    }
    else{
        cout << "the patient went insane because you didn't save enough brain. ";
    }
    cout << "Thanks for playing!" << endl;
    player_location = 100;

}

// main function
int main(){
    int play_game;
    int lives = 3;
    int score = 0;

    // (almost) all of the text to be used in the game is right here. 8 of everything for the 8 main brain sections to visit
    string locations[8] = {"Parietal Lobe", "Frontal Lobe", "Hypothalamus", "Occipital lobe", "Hippocampus", "Cerebellum", 
                            "Temporal lobe", "Spinal cord"};

    string trivia[8] = {"The Parietal lobe handles stimuli to your senses from the environment. (Sight is left for the Occipital lobe.)", 
                        "The Frontal lobe manages emotions and conscious thought.",  
                        "The Hypothalamus (and pituitary gland) regulate bodily automatic functions, like body temperature and hormones", 
                        "The Occipital lobe is responsible for taking in information from your eyes. (Specializes in sight)",
                        "The Hippocampus takes short-term memory, processes it, and sends it to long-term (the Temporal Lobe).",
                        "The Cerebellum is in charge of motor control and muscle memory.", 
                        "The Temporal lobe handles long-term memory and language.",
                        "The Spinal cord takes all of the instructions that the brain has and sends it out to the rest of the body."};
    string problems[8] = {"The patient is numb!", 
                            "The patient just mirrors facial expressions, there's no transformation happening to the stimuli.",
                            "Even cookies don't motivate the patient to sanity. The dopamine receptors must be worn down.",
                            "The patient either is silent or screams, especially at octopi. That's a weird bias.",
                            "Time between neurons firing is low, and the patient is feverish. Maybe if they had less to process?",
                            "The patient is trembling. Every stimulus produces tiny, irrelevant motions everywhere.",
                            "The patient was coherent momentarily, then lost all progress. It seems that learning things is difficult.",
                            "No matter what the rest of the brain says, the patient just waves their arms. "};
    
    string parietal_lobe_solution = "Input Layer";
    string frontal_lobe_solution = "Hidden Layers";
    string hypothalamus_solution = "Reward function";
    string occipital_lobe_solution = "Bias neuron";
    string hippocampus_solution = "Optimization Algorithm";
    string cerebellum_solution = "Activation Function";
    string temporal_lobe_solution = "Training method";
    string spinal_cord_solution = "Output layer";

    string tools[8] = {parietal_lobe_solution, frontal_lobe_solution, hypothalamus_solution, occipital_lobe_solution, 
                        hippocampus_solution, cerebellum_solution, temporal_lobe_solution, spinal_cord_solution};
    int player_location = 0;
    
    //  ------------- GAMEPLAY --------------

    title_screen(play_game);
    intro_text(play_game);

    // game loop
    while(lives >= 0 && player_location <8){
        player_choice(player_location, trivia, problems, tools, lives, score);
        if (player_location < 7){
            player_move(player_location, locations);
            cout << "\n";
        }
        // these run when the player is at the end, or they check if the player has failed
        else if(player_location == 7){
            player_too_far(score, player_location);
        }
        lost_lives(lives, player_location);
        cout << "Current score: " << score << endl;
    }
    return 0;
}