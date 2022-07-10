#pragma once
#include "IGameMode.h"
#include "Item.h"
#include "Question.h"

#include <random>
#include <queue>

struct UGameMode : public IGameMode
{
private:
    size_t Rounds{ 3 };
    size_t HealthPoints{ 1 };
    size_t ExperiencePoints{ 0 };
    size_t AnsweredQuestions{ 0 };
    wstring Name;
    ItemMap Items;
    queue<QuestionP> QuestionsQueue;

    size_t ItemsPerQuestion{ 4 };

    default_random_engine dre;

public:
    virtual void StartGame() override;
    virtual void FinishGame() override;

public:
    UGameMode(const wstring& name, const ItemMap& item_map);

private:
    const QuestionP GetNextQuestion();
    void ReturnQuestion(const QuestionP question);
    bool AskQuestion(QuestionP question);
    void ReduceHP(const size_t amount);
    void IncreaseEP(const size_t amount);
    inline bool ShouldStep() { return !QuestionsQueue.empty() && (HealthPoints > 0); };
    inline bool HasWon() { return QuestionsQueue.empty() && HealthPoints > 0; }

private:
    void Initialize();
    void Loop();
    void Step();
    void Status();

    void GenerateQuestions(const size_t amount, const size_t itemsPerQuestion, const ItemMap& items, queue<QuestionP>& Out);
    static ItemP GenerateAnswer(ItemVector& items, default_random_engine& in_dre);
    static ItemVector GetAvailableVariants(const ItemMap& items, const ItemP& item);
    static ItemMap GenerateQuestionVariants(ItemVector& items, const ItemP& answer, const size_t itemsPerQuestion, default_random_engine& in_dre);
};

