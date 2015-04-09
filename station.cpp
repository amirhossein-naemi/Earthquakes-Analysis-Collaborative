//-----------------------------------------------------------------------------
//
// Earthquakes' Events Analysis
// By Amirhossein Naemi
// March, 2015
// GIT: https://github.com/amirhossein-naemi/Earthquakes-Analysis-v3
//
//-----------------------------------------------------------------------------

#include "station.h"
// to use some functions like toupper_str
#include "earthquake.h"

int network_code_enum(string str_net_code) {
    // Case Sensitive
    if (str_net_code == "CE")
        return 0;
    if (str_net_code == "CI")
        return 1;
    if (str_net_code == "FA")
        return 2;
    if (str_net_code == "NP")
        return 3;
    if (str_net_code == "WR")
        return 4;
    return -1;
}

int type_of_band_enum(string str_type_of_band) {
    
    str_type_of_band = toupper_str_C(str_type_of_band);
    toupper_str(str_type_of_band);
    
    if (str_type_of_band == "LONG-PERIOD")
        return 0;
    if (str_type_of_band == "SHORT-PERIOD")
        return 1;
    if (str_type_of_band == "BROADBAND")
        return 2;
    return -1;
}

string type_of_inst_string(types_of_instrument type_of_inst) {
    
    switch (type_of_inst) {
        case High_Gain:
            return "High Gain";
        case Low_Gain:
            return "Low Gain";
        case Accelerometer:
            return "Accelerometer";
        default:
            return "ILLEGAL";
    }
}

// check for rest of the errors
bool is_there_any_err(station st) {
    
    //if (st.get_network_code() <1 || st.get_network_code() >5) // err
    //    return true;
    
    return false;
}

bool isok_station_code(string str){
    // Station code: Case sensitive: Must be either 3 alphabetic characters in
    // capital letters, or 5 numeric characters to be valid. station_code:
    // Case Sensitive : Must be either 3 alphabetic characters in
    // capital letters, or 5 numeric characters to be valid.string ssn;
    if (str.size() == 3)
    {
        for (int i = 0; i < 3; i++)
        {
            if (!isalpha(str[i]))
                return false;
            if (!isupper(str[i]))
                return false;
        }
        
        // if return true, means everything is fine
        return true;
    }
    
    if (str.size() == 5)
    {
        for (int i = 0; i < 5; i++)
            if (!isdigit(str[i]))
                return false;
        
        // if return true, means everything is fine
        return true;
    }
    
    return false;
}


bool isok_Orientation(string str){
    // Orientation: Case insensitive: a one to three characters combination.
    // Each character can be any of the following two options (alphabetic or
    // numeric, but not a combination of both):
    // N, E, or Z (one, two or three chars)
    // 1, 2, or 3 (one, two or three chars)
    
    toupper_str(str);
    size_t n = str.size();
    if (!isdigit(str[0]))
    {
        for (size_t i = 0; i < n; i++)
            if (!(str[i] == 'N' || str[i] == 'E' || str[i] == 'Z'))
                return false;
    }
    else
    {
        for (size_t i = 0; i < n; i++)
            if (!(str[i] == '1' || str[i] == '2' || str[i] == '3'))
                return false;
    }
    
    return true;
}

bool station::set_orientation(string a) {
    try
    {
        if (!isok_Orientation(a))
            throw (51);
        else
            Orientation = a;
        
        return true;
    }
    catch (int e)
    {
        //cout << "Value of Orientation is invalid" << e << endl;
        return false;
    }
}

bool station::set_station_name(string a) {
    try
    {
        if (!isok_station_code(a))
            throw (51);
        else
            station_name = a;
        return true;
    }
    catch (int e)
    {
        //cout << "Value of station name is invalid" << e << endl;
        return false;
    }
}

bool isok_network_code(string str){

    if (str.size() == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            if (!isalpha(str[i]))
                return false;
            if (!isupper(str[i]))
                return false;
        }
        // if return true, means everything is fine
        return true;
    }
    return false;
}

string network_codes_str[5] = { "CE", "CI", "FA", "NP", "WR" };
string station::get_network_code_str(){
    return network_codes_str[network_code];
}

bool station::set_network_code(network_codes network_codes_value){
    try
    {
        network_code = network_codes_value;
        return true;
    }
    catch (int e)
    {
        //cout << "Value of station name is invalid" << e << endl;
        return false;
    }
}

bool station::set_network_code(string network_codes_value){
    try
    {
        if (!isok_network_code(network_codes_value))
            throw (51);
        else
            network_code = (network_codes)network_code_enum(network_codes_value);
        return true;
    }
    catch (int e)
    {
        //cout << "Value of station name is invalid" << e << endl;
        return false;
    }
}

bool isok_type_of_band(string str){
    
    // Type of band: Case insensitive: One word. It can be any of the following
    // to be valid (the code in
    // parenthesis is for later reference):
    // string type_of_band;
    types_of_band t = (types_of_band)type_of_band_enum(str);
    if (t<0 || t>2) return false;
    return true;
}

bool station::set_type_of_band(types_of_band a){
    try
    {
        type_of_band = a;
        return true;
    }
    catch (int e)
    {
        //cout << "Value of station name is invalid" << e << endl;
        return false;
    }
}
bool station::set_type_of_band(string a){
    try
    {
        if (!isok_type_of_band(a))
            throw (51);
        else
            type_of_band = (types_of_band)type_of_band_enum(a);
        return true;
    }
    catch (int e)
    {
        //cout << "Value of station name is invalid" << e << endl;
        return false;
    }
}

int type_of_instrument_enum(string str_type_of_inst) {
    toupper_str(str_type_of_inst);
    //Case insensitive
    if (str_type_of_inst == "HIGH-GAIN")
        return 0;
    if (str_type_of_inst == "LOW-GAIN")
        return 1;
    if (str_type_of_inst == "ACCELEROMETER")
        return 2;
    return -1;
}

bool station::set_type_of_instrument(types_of_instrument a) {
    try
    {
        type_of_instrument = a;
        return true;
    }
    catch (int e)
    {
        //cout << "Value of station name is invalid" << e << endl;
        return false;
    }
}

bool station::set_type_of_instrument(string a){
    try
    {
        type_of_instrument =
            (types_of_instrument)type_of_instrument_enum(a);
        return true;
    }
    catch (int e)
    {
        //cout << "Value of station name is invalid" << e << endl;
        return false;
    }
}

string types_of_instrument_strf[3] = { "High_Gain", "Low_Gain",
    "Accelerometer" };
string types_of_instrument_str[3] = { "H", "L", "N" };
char types_of_instrument_char[3] = { 'H', 'L', 'N' };
string station::get_type_of_instrument_str(){
    return types_of_instrument_str[type_of_instrument];
}

string types_of_band_strf[3] = { "Longperiod", "Shortperiod", "Broadband" };
string types_of_band_str[3] = { "L", "B", "H" };
char types_of_band_char[3] = { 'L', 'B', 'H' };
string station::get_type_of_band_str(){
    return types_of_band_str[type_of_band];
}
