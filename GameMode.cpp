#include "GameMode.h"
#include <algorithm>
//#include <format>
#include <iostream>

using namespace std;

void UGameMode::StartGame()
{
    Initialize();
    wcout << L"------------------------------------------------\n";
    wcout << L"The Game '" << Name << "' has started!\n";
    Status();
    Loop();
}

void UGameMode::FinishGame()
{
    const char* form = AnsweredQuestions == 1 ? "!\n" : "s!\n";
    wcout << L"------------------------------------------------\n";
    wcout << "The game has ended\n\n";
    wcout << "You answered: " << AnsweredQuestions << " question" << form;
    wcout << "And earned: " << ExperiencePoints << " point" << form;
    wcout << L"------------------------------------------------\n";
    const char* result = HasWon() ? "YOU WON!!!\n" : "You lost...\n";
    wcout << result;
    wcout << L"................................................\n\n\n";
}

UGameMode::UGameMode(const wstring& name, const ItemMap& item_map)
    : Name{name}
    , Items{item_map}
{
    dre = default_random_engine{ random_device{}()};
}

void UGameMode::Initialize()
{
    // in case when game mode has more rounds than actual items
    AnsweredQuestions = 0;
    ExperiencePoints = 0;
    Rounds = min(Rounds, Items.size());
    GenerateQuestions(Rounds, ItemsPerQuestion, Items, QuestionsQueue);
}

void UGameMode::Loop()
{
    while (ShouldStep())
    {
        Step();
    }

    FinishGame();
}



void UGameMode::Step()
{
    const auto question = GetNextQuestion();
    const auto result = AskQuestion(question);
    if (result)
    {
        IncreaseEP(1);
        ++AnsweredQuestions;
    }
    else
    {
        ReduceHP(1);
        ReturnQuestion(question);
    }
    Status();
}

void UGameMode::Status()
{
    wcout << L"------------------------------------------------\n";
    wcout << "Your XP: " << ExperiencePoints << " \n";
    wcout << "Your HP: " << HealthPoints << " \n";
    wcout << L"------------------------------------------------\n";
}

bool UGameMode::AskQuestion(QuestionP question)
{
    wcout << *question.get();
    wcin >> *question.get();
    return question->IsValidAnswer();
}

const QuestionP UGameMode::GetNextQuestion()
{
    const auto question = QuestionsQueue.front();
    QuestionsQueue.pop();
    return question;
}

void UGameMode::ReturnQuestion(const QuestionP question)
{
    QuestionsQueue.emplace(question);
}

void UGameMode::ReduceHP(const size_t amount)
{
    if (HealthPoints <= amount)
    {
        HealthPoints = 0;        
    }
    else
    {
        HealthPoints -= amount;
    }    
}

void UGameMode::IncreaseEP(const size_t amount)
{
    ExperiencePoints += amount;
}

ItemVector UGameMode::GetAvailableVariants(const ItemMap& items, const ItemP& item)
{
    ItemVector result;
    for (const auto& pair : items)
    {
        if (pair.first != item->Name)
        {
            result.emplace_back(pair.second);
        }
    }

    return result;
}

ItemP UGameMode::GenerateAnswer(ItemVector& items, default_random_engine& in_dre)
{
    shuffle(items.begin(), items.end(), in_dre);
    const auto answer = items.back();
    items.pop_back();
    return answer;
}

ItemMap UGameMode::GenerateQuestionVariants(ItemVector& items, const ItemP& answer, const size_t itemsPerQuestion, default_random_engine& in_dre)
{
    shuffle(items.begin(), items.end(), in_dre);
    ItemVector temp{ items.end() - itemsPerQuestion, items.end() };
    temp.emplace_back(answer);
    shuffle(temp.begin(), temp.end(), in_dre);

    items.erase(items.end() - itemsPerQuestion, items.end());

    ItemMap result;
    for (const auto& item : temp)
    {
        result[item->Name] = item;
    }

    shuffle(items.begin(), items.end(), in_dre);

    return result;
}

void UGameMode::GenerateQuestions(const size_t amount, const size_t itemsPerQuestion, const ItemMap& items, queue<QuestionP>& out)
{
    queue<QuestionP> output;
    ItemVector leftItems;

    for (const auto& item : items)
    {
        leftItems.emplace_back(item.second);
    }

    for (size_t i = 0; i < amount; ++i)
    {
        const auto answer = GenerateAnswer(leftItems, dre);
        auto candidates = GetAvailableVariants(items, answer);
        const auto variants = GenerateQuestionVariants(candidates, answer, itemsPerQuestion - 1, dre);

        QuestionP result = make_shared<UQuestion>( UQuestion{answer, variants });
        output.push(result);
    }

    swap(out, output);
}
