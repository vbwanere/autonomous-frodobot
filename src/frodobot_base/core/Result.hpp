#pragma once

#include <string>
#include <stdexcept>

namespace frodobot
{
    // Error type - every error in the system returns this
    struct Error
    {
        std::string code; // machine readable
        std::string message; // human readable 
    };

    template<typename T, typename E = Error>

    class Result {
        public:

        // --- Constructors ---
        // called when operation succeeds
        static Result ok(T value) {
            Result r;
            r.m_ok = true;
            r.m_value = value;
            return r;
        }

        static Result fail(E error) {
            Result r;
            r.m_ok = false;
            r.m_error = error;
            return r;
        }

        // --- Queries ---
        bool isOk() const { 
            return m_ok; 
        }
        
        bool isFail() const {
            return !m_ok;
        }

        // --- Accessors ---
        const T& value() const {
            if (!m_ok)
                throw std::logic_error("Called value() on a failed Result");
            return m_value;
        }

        const E& error() const {
            if (m_ok)
                throw std::logic_error("Called error() on a successful Result");
            return m_error;
        }

        private:
        bool m_ok = false;
        T m_value {};
        E m_error {};
    };
    

} // namespace frodobot