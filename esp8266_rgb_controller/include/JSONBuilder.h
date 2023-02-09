#ifndef JSON_BUILDER
#define JSON_BUILDER

#include <string>
#include <sstream>

class JSONBuilder
{
private:
    std::stringstream m_stream;
    bool m_use_array;
public:
    JSONBuilder(bool use_array = false):
        m_use_array{use_array}
    {
        m_stream << (m_use_array ? '[' : '{');
    }
    JSONBuilder* push(std::string entry)
    {
        if (m_use_array)
            m_stream << entry << ',';

        return this;
    }
    JSONBuilder* addPair(std::string key, std::uint8_t value)
    {
        m_stream << "\"" << key << "\": \"" << (int)value << "\",";
        return this;
    }
    JSONBuilder* addPair(std::string key, std::string value)
    {
        m_stream << "\"" << key << "\": \"" << value << "\",";
        return this;
    }
    JSONBuilder* addPair(std::uint8_t key, std::string value)
    {
        m_stream << "\"" << (int)key << "\": \"" << value << "\",";
        return this;
    }
    std::string build()
    {
        std::string data = m_stream.str();
        std::string json = data.substr(0, data.size()-1);

        json += (m_use_array ? ']' : '}');
        return json;
    }

};

#endif
