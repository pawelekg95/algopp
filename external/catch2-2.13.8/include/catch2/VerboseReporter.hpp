////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author Jakub Sejdak
/// @copyright TRUMPF Huettinger
///
/// Copyright (c) 2019-2020, TRUMPF Huettinger
/// All rights reserved.
///
////////////////////////////////////////////////////////////////////////

#pragma once

#include <catch2/catch.hpp>

#include <cstdint>
#include <sstream>
#include <string>

constexpr std::size_t cIndentationSize = 4;
constexpr std::size_t cStatusColumn = 100;
const char* cErrorSeparator = "====================";

namespace Catch
{

class VerboseReporter : public StreamingReporterBase<VerboseReporter>
{
public:
    explicit VerboseReporter(const ReporterConfig& config)
        : StreamingReporterBase(config)
    {
        m_reporterPrefs.shouldRedirectStdOut = false;
    }

    static std::string getDescription()
    {
        return "Reports test results in a similar way to Google Test";
    }

private:
    void testCaseStarting(const TestCaseInfo& testInfo) override
    {
        StreamingReporterBase::testCaseStarting(testInfo);
        m_testTimer.start();

        stream << "Start TEST CASE " << testInfo.name << "\n";
        stream.flush();
    }

    void sectionStarting(const SectionInfo& sectionInfo) override
    {
        StreamingReporterBase::sectionStarting(sectionInfo);
        m_lastSection = sectionInfo.name;

        increaseIndentation();

        stream << indentation() << "Start SECTION: " << sectionInfo.name
               << "\n";
        stream.flush();
    }

    void assertionStarting(const AssertionInfo&) override {}

    bool assertionEnded(const AssertionStats& assertionStats) override
    {
        const AssertionResult& result = assertionStats.assertionResult;
        if (result.isOk())
            return true;

        stream << indentation() << cErrorSeparator << "\n";
        increaseIndentation();
        stream << indentation()
               << "Failed test    : " << m_sectionStack.back().name << "\n";
        stream << indentation() << "Last section   : " << m_lastSection << "\n";
        stream << indentation() << "Failed line    : " << result.getSourceInfo()
               << "\n";
        stream << indentation() << "Type           : ";
        switch (result.getResultType())
        {
            case ResultWas::ExpressionFailed:
                stream << "Expression failed";
                break;
            case ResultWas::ThrewException:
                stream << "Unexpected exception";
                break;
            case ResultWas::FatalErrorCondition:
                stream << "Fatal error condition";
                break;
            case ResultWas::DidntThrowException:
                stream << "No exception was thrown where one was expected";
                break;
            case ResultWas::ExplicitFailure:
                stream << "Explicit failure";
                break;
            default:
                return true;
        }
        stream << "\n";

        if (!assertionStats.infoMessages.empty())
        {
            stream << indentation() << "Message(s)     : "
                   << assertionStats.infoMessages[0].message << "\n";
            for (std::size_t i = 1; i < assertionStats.infoMessages.size(); ++i)
                stream << "                         "
                       << assertionStats.infoMessages[i].message << "\n";
        }

        if (result.hasExpression())
        {
            stream << indentation()
                   << "Expression     : " << result.getExpressionInMacro()
                   << "\n";
            stream << indentation()
                   << "With expansion : " << result.getExpandedExpression()
                   << "\n";
        }

        decreaseIndentation();
        stream << indentation() << cErrorSeparator << "\n";
        stream.flush();

        return true;
    }

    void sectionEnded(const SectionStats& sectionStats) override
    {
        std::stringstream ss;
        ss << indentation() << "End";
        stream << ss.str();
        stream.flush();
        printStatus(ss.str().size(), sectionStats.assertions.allOk());

        decreaseIndentation();

        StreamingReporterBase::sectionEnded(sectionStats);
    }

    void testCaseEnded(const TestCaseStats& testCaseStats) override
    {
        auto elapsedMs = m_testTimer.getElapsedMilliseconds();
        std::stringstream ss;
        ss << "End [" << elapsedMs << " ms]";
        stream << ss.str();
        printStatus(ss.str().size(), testCaseStats.totals.assertions.allOk());

        m_lastSection.clear();
        StreamingReporterBase::testCaseEnded(testCaseStats);
    }

    void testRunEnded(const TestRunStats& testRunStats) override
    {
        stream << "\n";
        stream << std::string(cStatusColumn, '=') << "\n";
        stream << "Finished TEST RUN : " << testRunStats.runInfo.name << "\n";
        stream << "Status            :";

        const auto& assertions = testRunStats.totals.assertions;
        printStatus(cStatusColumn, assertions.allOk(), true);
        stream << "Failed assertions : " << assertions.failed << " / "
               << assertions.total() << "\n";
        stream.flush();

        StreamingReporterBase::testRunEnded(testRunStats);
    }

    std::string indentation() { return std::string(m_indentation, ' '); }
    void increaseIndentation() { m_indentation += cIndentationSize; }
    void decreaseIndentation() { m_indentation -= cIndentationSize; }

    void printStatus(std::size_t offset, bool success, bool finalStatus = false)
    {
        auto paddingSize =
            (cStatusColumn > offset) ? (cStatusColumn - offset) : 1;
        stream << std::string(paddingSize, ' ');

        if (success)
        {
            Colour color(Colour::Green);
            stream << (finalStatus ? "[PASSED]" : "[OK]");
        }
        else
        {
            Colour color(Colour::Red);
            stream << "[FAILED]";
        }

        stream << "\n";
        stream.flush();
    }

private:
    Timer m_testTimer;
    std::size_t m_indentation{};
    std::string m_lastSection;
};

CATCH_REGISTER_REPORTER("verbose", VerboseReporter) // NOLINT

} // end namespace Catch
