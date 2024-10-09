#include <iostream>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

const string green = "\033[1;32m";
const string blue = "\033[1;34m";
const string yellow = "\033[1;33m";
const string red = "\033[1;31m";
const string cyan = "\033[1;36m";
const string reset = "\033[0m";

struct Question {
    string text;
    string options[4];
    int correctanswer;
};

vector<Question> questions;

void initializequestions() {
    questions.push_back({ "What is the longest river in the world?", {"1. Amazon", "2. Nile", "3. Mississippi", "4. Volga"}, 1 });
    questions.push_back({ "Who painted the Mona Lisa?", {"1. Pablo Picasso", "2. Vincent van Gogh", "3. Leonardo da Vinci", "4. Michelangelo"}, 2 });
    questions.push_back({ "What is the largest technology company in South Korea?", {"1. LG", "2. Hyundai", "3. Samsung", "4. Kia"}, 2 });
    questions.push_back({ "What is the chemical symbol for water?", {"1. CO2", "2. H2O", "3. O2", "4. N2"}, 1 });
    questions.push_back({ "What is the largest organ in the human body?", {"1. Brain", "2. Heart", "3. Liver", "4. Skin"}, 3 });
    questions.push_back({ "How many days are there in a year?", {"1. 365", "2. 366", "3. 364", "4. 360"}, 0 });
    questions.push_back({ "What is a house made entirely of ice called?", {"1. Igloo", "2. Cabin", "3. Brick House", "4. Tent"}, 0 });
    questions.push_back({ "What is the capital of Portugal?", {"1. Madrid", "2. Rome", "3. Lisbon", "4. Paris"}, 2 });
    questions.push_back({ "How many breaths does the human body take per day?", {"1. 10,000", "2. 15,000", "3. 20,000", "4. 30,000"}, 2 });
    questions.push_back({ "Who was the British Prime Minister from 1841 to 1846?", {"1. Winston Churchill", "2. Robert Peel", "3. Margaret Thatcher", "4. Tony Blair"}, 1 });
}

void loadingAnimation()
{
    const string loadingmessage = "Loading";
    for (int i = 0; i < 10; i++)
    {
        cout << "\r" << cyan << loadingmessage << string(i % 4, '.') << reset;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "\r" << reset << "                    " << endl;
}

void mainmenu(int selected)
{
    const string options[2] = { "Admin", "Guest" };
    const int consolewidth = 50;

    cout << setw(consolewidth / 2 + 12) << green << "Welcome to the Quiz Game!" << reset << endl;

    for (int i = 0; i < 2; i++)

    {
        cout << (i == selected ? blue + "> " : "  ") << options[i] << reset << endl;
    }
}

void adminmenu(int selected) {
    const string options[3] = { "Create New Quiz", "View Quizzes", "Exit" };
    const int consolewidth = 50;

    cout << setw(consolewidth / 2 + 12) << green << "Admin Menu" << reset << endl;

    for (int i = 0; i < 3; i++) {
        cout << (i == selected ? blue + "> " : "  ") << options[i] << reset << endl;
    }
}

void addnewquestions(vector<Question>* quiz)
{
    Question newquestion;
    cout << yellow << "Enter the question : " << reset;
    cin.ignore();
    getline(cin, newquestion.text);

    for (int i = 0; i < 4; i++)
    {
        cout << yellow << "Enter option " << (i + 1) << " : " << reset;
        getline(cin, newquestion.options[i]);
    }

    cout << yellow << "Enter the correct answer (1-4) : " << reset;
    cin >> newquestion.correctanswer;
    newquestion.correctanswer--;

    quiz->push_back(newquestion);
    cout << green << "Question successfully added!" << reset << endl;
}

void editquestion(Question* question)
{
    cout << cyan << "Editing Question : " << question->text << reset << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << "Option " << (i + 1) << ": " << question->options[i] << endl;
    }

    cout << "Current Answer : " << question->correctanswer + 1 << endl;

    cout << yellow << "Enter the new question (press Enter to keep the same) : " << reset;
    string newquestiontext;
    cin.ignore();
    getline(cin, newquestiontext);

    if (!newquestiontext.empty())
    {
        question->text = newquestiontext;
    }

    for (int i = 0; i < 4; i++)
    {
        cout << yellow << "Enter the new option " << (i + 1) << " (press Enter to keep the same) : " << reset;
        string newoptext;
        getline(cin, newoptext);

        if (!newoptext.empty()) {
            question->options[i] = newoptext;
        }
    }

    cout << yellow << "Enter the new correct answer (1-4, press 0 to keep the same)  : " << reset;
    int newcoranswer;
    cin >> newcoranswer;

    if (newcoranswer > 0 && newcoranswer <= 4)
    {
        question->correctanswer = newcoranswer - 1;
    }

    cout << green << "Question successfully updated !" << reset << endl;
}

void viewquestions(vector<Question>* quiz)
{
    if (quiz->empty())
    {
        cout << red << "No questions available." << reset << endl;
    }

    else
    {
        for (int i = 0; i < quiz->size(); i++)
        {
            cout << "Question " << i + 1 << ": " << (*quiz)[i].text << endl;
            cout << "Answer : " << (*quiz)[i].correctanswer + 1 << endl;
        }

        cout << yellow << "Enter the question number to edit (press 0 to go back) : " << reset;
        int editindx;
        cin >> editindx;

        if (editindx > 0 && editindx <= quiz->size())
        {
            editquestion(&(*quiz)[editindx - 1]);
        }
    }
    cout << cyan << "Press any key to return to the admin menu..." << reset << endl;
    _getch();
}

void clearcons() {
    cout << "\033[H\033[J";
}

void takequiz(const vector<Question>* quiz)
{
    if (quiz->size() < 10)
    {
        cout << red << "Not enough questions. Please add at least 10 questions." << reset << endl;
        _getch();
        return;
    }

    vector<int> randomindices;

    while (randomindices.size() < 10)
    {
        int randindex = rand() % quiz->size();
        if (find(randomindices.begin(), randomindices.end(), randindex) == randomindices.end())
        {
            randomindices.push_back(randindex);
        }
    }

    int score = 0;
    int selectedop = 0;

    for (int i = 0; i < 10; i++)
    {
        int questionindx = randomindices[i];
        cout << cyan << "Question " << (i + 1) << ": " << (*quiz)[questionindx].text << reset << endl;

        for (int j = 0; j < 4; j++)
        {
            cout << (j == selectedop ? blue + "> " : "  ") << (*quiz)[questionindx].options[j] << reset << endl;
        }

        char ch;
        while (true)
        {
            ch = _getch();
            if (ch == 72)
            {
                selectedop = (selectedop - 1 + 4) % 4;
            }
            else if (ch == 80)
            {
                selectedop = (selectedop + 1) % 4;
            }
            else if (ch == 13)
            {
                break;
            }

            clearcons();
            cout << cyan << "Question " << (i + 1) << ": " << (*quiz)[questionindx].text << reset << endl;

            for (int j = 0; j < 4; j++) {
                cout << (j == selectedop ? blue + "> " : "  ") << (*quiz)[questionindx].options[j] << reset << endl;
            }
        }

        if (selectedop == (*quiz)[questionindx].correctanswer)
        {
            cout << green << "Correct!" << reset << endl;
            score++;
        }
        else {
            cout << red << "Wrong!" << reset << endl;
        }

        this_thread::sleep_for(chrono::seconds(1));
        clearcons();
    }

    cout << yellow << "Score : " << score << "/10" << reset << endl;
    cout << cyan << "Press any key to return to the main menu..." << reset << endl;
    _getch();
}

int main()
{
    srand(time(0));
    initializequestions();
    loadingAnimation();

    int mainselected = 0;
    int adminselected = 0;

    while (true)
    {
        clearcons();
        mainmenu(mainselected);

        char ch = _getch();
        if (ch == 72) {
            mainselected = (mainselected - 1 + 2) % 2;
        }
        else if (ch == 80)
        {
            mainselected = (mainselected + 1) % 2;
        }
        else if (ch == 13)
        {
            if (mainselected == 0)
            {
                while (true)
                {
                    clearcons();
                    adminmenu(adminselected);

                    char adminchart = _getch();
                    if (adminchart == 72)
                    {
                        adminselected = (adminselected - 1 + 3) % 3;
                    }
                    else if (adminchart == 80)
                    {
                        adminselected = (adminselected + 1) % 3;
                    }
                    else if (adminchart == 13)
                    {
                        if (adminselected == 0)
                        {
                            addnewquestions(&questions);
                        }
                        else if (adminselected == 1)
                        {
                            viewquestions(&questions);
                        }
                        else if (adminselected == 2)
                        {
                            break;
                        }
                    }
                }
            }
            else if (mainselected == 1)
            {
                takequiz(&questions);
            }
        }
    }

    return 0;
}
