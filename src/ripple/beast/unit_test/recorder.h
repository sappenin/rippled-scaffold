//
// Copyright (c) 2013-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BEAST_UNIT_TEST_RECORDER_HPP
#define BEAST_UNIT_TEST_RECORDER_HPP

#include <ripple/beast/unit_test/results.h>
#include <ripple/beast/unit_test/runner.h>

namespace beast {
namespace unit_test {

/** A test runner that stores the results. */
class recorder : public runner
{
private:
    results m_results;
    suite_results m_suite;
    case_results m_case;

public:
    recorder() = default;

    /** Returns a report with the results of all completed suites. */
    results const&
    report() const
    {
        return m_results;
    }

private:
    virtual void
    on_suite_begin(suite_info const& info) override
    {
        m_suite = suite_results(info.full_name());
    }

    virtual void
    on_suite_end() override
    {
        m_results.insert(std::move(m_suite));
    }

    virtual void
    on_case_begin(std::string const& name) override
    {
        m_case = case_results(name);
    }

    virtual void
    on_case_end() override
    {
        if (m_case.tests.size() > 0)
            m_suite.insert(std::move(m_case));
    }

    virtual void
    on_pass() override
    {
        m_case.tests.pass();
    }

    virtual void
    on_fail(std::string const& reason) override
    {
        m_case.tests.fail(reason);
    }

    virtual void
    on_log(std::string const& s) override
    {
        m_case.log.insert(s);
    }
};

}  // namespace unit_test
}  // namespace beast

#endif
