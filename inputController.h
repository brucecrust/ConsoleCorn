#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "entity.h"
#include "map.h"
#include "rawmode.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>

class InputController {
    public:
        void movement(Map* p_space, Entity p_entity) {
            p_space->setOperatingEntity(p_entity);

            enableRawMode();

            char c;
            while (read(STDIN_FILENO, &c, 1) == 1) {
                switch(c) {
                    case 'w' :
                        p_space->modifySpace(-1, 0);
                        break;
                    case 's' :
                        p_space->modifySpace(1, 0);
                        break;
                    case 'a' :
                        p_space->modifySpace(0, -1);
                        break;
                    case 'd' :
                        p_space->modifySpace(0, 1);
                        break;
                    case 'e' :
                        disableRawMode();
                        userInput();
                        break;
                    case 'q':
                        disableRawMode();
                        exit(1);
                        break;
                    default:
                        std::cout << "Invalid movement." << std::endl;
                }

                disableRawMode();
                break;
            }
    }

    std::string handleEntries(std::vector<std::string> p_acceptableInput) {
        std::cout << "Choices: " << std::endl;
        for (std::string i : p_acceptableInput) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        std::string acceptedInput;

        for (;;) {
            std::string input;
            std::cin >> input;

            std::vector<std::string> inputVector;
            
            for (std::string i : p_acceptableInput) {
                if (std::find(p_acceptableInput.begin(), p_acceptableInput.end(), i) != p_acceptableInput.end()) {
                    if (i.rfind(input, 0) == 0) inputVector.push_back(i);
                }
            }

            if (inputVector.size() == 0) {
                std::cout << "Invalid input." << std::endl;
            } else if (inputVector.size() == 1) {
                acceptedInput = inputVector[0];
                break;
            } else {
                std::cout << "Which of the following did you mean?: " << std::endl;
                for (std::string i : inputVector) {
                    std::cout << i << std::endl;
                }
            }
        }

        std::cout << "You picked: " << acceptedInput << std::endl;
        return acceptedInput;
    }

    void userInput() {
        std::vector<std::string> acceptableInput = { "fireball", "firestorm", "iceball", "lightning", "telekinis", "teleport" };
        std::string input = handleEntries(acceptableInput);
    }

    private:
        char m_userEntry;
        
};

#endif