#include "Question.h"

wostream& operator<<(wostream& os, const UQuestion& question)
{
    os << L"Which one of the variants is " << question.Answer->Name << L":\n";

    auto it = question.Variants.begin();
    auto end = question.Variants.end();

    while (it != end)
    {
        os << it->first;
        if (next(it) != end)
        {
            os << "    ";
        }

        ++it;
    }

    os << "\n";
    os << "Type in the name of the variant: ";

    return os;
}

wistream& operator>>(wistream& is, UQuestion& question)
{
    is >> question.Guess;
    return is;
}

bool UQuestion::IsValidAnswer() const
{
    const auto& it = Variants.find(Guess);
    if (it == Variants.end())
    {
        return false;
    }

    return it->second == Answer;
}