#ifndef JSON_BUILDER
#define JSON_BUILDER

#include <string>
#include <sstream>

class JSONBuilder
{
private:
    std::stringstream m_stream;
    /**
     * Is the main container an array;
     * 
     */
    bool m_is_array;
public:
    JSONBuilder(bool is_array = false):
        m_is_array{is_array}
    {
        m_stream << (m_is_array ? '[' : '{');
    }
    JSONBuilder* push(std::string entry)
    {
        if (m_is_array)
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

        json += (m_is_array ? ']' : '}');
        return json;
    }

};

#endif
