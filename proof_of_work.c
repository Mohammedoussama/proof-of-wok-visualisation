#include <raylib.h>
#include <stdlib.h>
#include <time.h>  
#include <stdio.h> 

void hash_rnd(char *randed, int length) {
    char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length; i++) {
        randed[i] = chars[rand() % 36];
    }
    randed[length] = '\0';  // gpt-ed , to terminate string
}
int main() {
    InitWindow(1300,850, "Hash Code Animation");

    srand(time(0)); //seeded rand ra7 yrandi b seed mn 1970 lrk in secs

    Texture2D telegram= LoadTexture("C:/Users/leNOVO/Downloads/660619.png");
    Texture2D node= LoadTexture("C:/Users/leNOVO/Downloads/cube noir.png");  
    Texture2D greennode= LoadTexture("C:/Users/leNOVO/Downloads/cube vert.png");

    // animation vars
    bool ssending = false;           
    int currentNode = 1;              
    double startTime = 0;          
    double sendtime = 2;            
    Vector2 telestart = {0, 0};       
    Vector2 teleend = {0, 0};          
    Vector2 telepos = {0, 0};        
    bool nodesReceived[4]= {false, false, false, false}; // Track which nodes received the hash

    // hash search variables
    bool hashing = true;         
    double searchStartTime = GetTime();
    char currentCode[9];              
    char foundCode[9];              
    bool hashFound = false;

        Vector2 nPosition[4]= { //raylib custom structure hold 2 stuff
        {100, 350}, {1050, 180}, {1050, 350}, {1050, 520}};

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);

        for (int i = 0; i < 4; i++) {//nodes
            Texture2D klch = nodesReceived[i] ? greennode : node;  // condition ? if true : if false
            DrawTextureEx(klch, nPosition[i], 0, 0.1f, WHITE);
        }
        if (ssending) {//telegram
            DrawTextureEx(telegram, telepos, 0, 0.2f, WHITE);
        }
        if (hashing) {//hashing
            DrawText("Searching for hash...", 85, 510, 20, BLACK);
            DrawText(currentCode, 85, 540, 30, RED);
        } else if (hashFound) {
            DrawText("Hash found!", 85, 510, 20, GREEN);
            DrawText(foundCode, 85, 540, 30, GREEN);}

        EndDrawing();
        
        if (hashing) {//hash anim
            if (GetTime() - searchStartTime < 4) { // get time = lw9t in secs - time the program started ...> timer 
                hash_rnd(currentCode, 8);
            } else {
                hashing = false;
                hashFound = true;
                hash_rnd(foundCode, 8);
                nodesReceived[0] = true;
            }
        }
        if (IsKeyPressed(KEY_SPACE) && !hashing ) {
            ssending =true;
            startTime =GetTime();                        
            telestart = {nPosition[0].x + 80, nPosition[0].y +30};
            teleend = {nPosition[currentNode].x -50 , nPosition[currentNode].y+30}; 
            telepos =telestart;                         
        }
        // Update send animation
        if (ssending) {
            double elapsed = GetTime() - startTime;// based on time it will increase t thats how the interpolation progress
            double t = elapsed / sendtime;                
            if (t >= 1.0) {                              
                t = 1.0;
                ssending = false;                       //verifi ida l7g 
                nodesReceived[currentNode] = true;       
                currentNode++;    }                      
            // Interpolate
            telepos.x =telestart.x + t * (teleend.x - telestart.x);
            telepos.y =telestart.y + t * (teleend.y - telestart.y);
        }

}
    // Cleans stuff if there were memory allocated 
    UnloadTexture(telegram);
    UnloadTexture(node);
    UnloadTexture(greennode);
    CloseWindow();
    return 0;
}
//this is our updater virsion that we did present
