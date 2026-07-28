#include <juce_core/juce_core.h>

int main(int, char**)
{
    juce::UnitTestRunner runner;
    runner.setAssertOnFailure(false);

    // Roda todos os juce::UnitTest registrados no processo -- hoje isso e
    // so o AudioEngineMixingTests, mas qualquer novo UnitTest adicionado ao
    // target wtracks_engine_tests entra automaticamente aqui.
    runner.runAllTests();

    int numFailures = 0;

    for (int i = 0; i < runner.getNumResults(); ++i)
    {
        if (const auto* result = runner.getResult(i))
            numFailures += result->failures;
    }

    return numFailures == 0 ? 0 : 1;
}