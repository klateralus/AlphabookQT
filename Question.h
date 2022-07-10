#pragma once

#include "Item.h"
#include <memory>
#include <iostream>

struct UQuestion;
typedef shared_ptr<UQuestion> QuestionP;

struct UQuestion
{
    UQuestion(const ItemP answer, const ItemMap variatns) : Answer(answer), Variants(variatns) {};
    bool IsValidAnswer(const ItemP variant) const { return Answer == variant; };
    bool IsValidAnswer() const;
    const ItemMap GetVariants() const { return Variants; };
    friend wostream& operator<<(wostream& os, const UQuestion& dt);
    friend wistream& operator>>(wistream& is, UQuestion& dt);
private:
    const ItemP Answer{ nullptr };
    const ItemMap Variants;
    wstring Guess;
};