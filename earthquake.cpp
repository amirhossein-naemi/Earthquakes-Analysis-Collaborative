//-----------------------------------------------------------------------------
//
// Earthquakes' Events Analysis
// By Amirhossein Naemi
// March, 2015
// GIT: https://github.com/amirhossein-naemi/Earthquakes-Analysis-v3
//
//-----------------------------------------------------------------------------

#include "earthquake.h"

int str2int(const std::string& str)
{
    int result = 0;
    
    std::string::const_iterator i = str.begin();
    
    if (i == str.end())
        return false;
    
    bool negative = false;
    
    if (*i == '-')
    {
        negative = true;
        ++i;
        
        if (i == str.end())
            return false;
    }
    
    result = 0;
    
    for (; i != str.end(); ++i)
    {
        if (*i < '0' || *i > '9')
            return false;
        
        result *= 10;
        result += *i - '0';
    }
    
    if (negative)
        result = -result;
    
    return result;
}


// **************************** month *****************************
const char *months2str[] = { "January", "February", "March", "April", "May",
    "June", "July", "August", "September", "October", "November", "December" };
string earthquake::get_month_str() { return months2str[month]; }

months mnth_str2enum(string mnth) {
    
    int imnth = str2int(mnth);
    
    switch (imnth) {
        case 1:
            return January;
        case 2:
            return February;
        case 3:
            return March;
        case 4:
            return April;
        case 5:
            return May;
        case 6:
            return June;
        case 7:
            return July;
        case 8:
            return August;
        case 9:
            return September;
        case 10:
            return  October;
        case 11:
            return November;
        case 12:
            return December;
    }
    return December;
}

void earthquake::set_month(string m) {
    try
    {
        month = mnth_str2enum(m);
    }
    catch (int e)
    {
        cout << "Value of month is invalid" << endl;
    }
}
void earthquake::set_month(months monthvalue) {
    try
    {
        month = monthvalue;
    }
    
    catch (int e)
    {
        cout << "Value of month is invalid" << endl;
    }
}

// **************************** day *****************************
void earthquake::set_day(int d) {
    try
    {
        if (d < 1 || d > 31)
            throw (20);
        else
            day = d;
    }
    catch (int e)
    {
        cout << "Value of dayy is invalid" << endl;
    }
}

void earthquake::set_day(string a){
    int b = str2int(a);
    set_day(b);
}

void earthquake::set_year(int y) {
    try
    {
        if (y < 1800 || y > 2100)
            throw (21);
        else
            yr = y;
    }
    catch (int e)
    {
        //cout << "An exception occurred. Exception Nr. " << e << '\n';
        cout << "Value of year is invalid" << e << endl;
    }
}

void earthquake::set_year(string a){
    try
    {
        int b = str2int(a);
        set_year(b);
    }
    catch (int e)
    {
        set_year(-1);
    }
}

void earthquake::set_hour(int a) {
    try
    {
        if (a < 0 || a > 24)
            throw (22);
        else
            hr = a;
    }
    catch (int e)
    {
        cout << "Value of hour is invalid" << e << endl;
    }
}

void earthquake::set_hour(string a){
    try
    {
        int b = str2int(a);
        set_hour(b);
    }
    catch (int e)
    {
        set_hour(-1);
    }
}

void earthquake::set_min(int a) {
    try
    {
        if (a < 0 || a > 59)
            throw (23);
        else
            min = a;
    }
    catch (int e)
    {
        cout << "Value of minute is invalid" << e << endl;
    }
}

void earthquake::set_min(string a){
    try
    {
        int b = str2int(a);
        set_min(b);
    }
    catch (int e)
    {
        set_min(-1);
    }
}

void earthquake::set_sec(int a) {
    try
    {
        if (a < 0 || a > 59)
            throw (22);
        else
            sec = a;
    }
    catch (int e)
    {
        cout << "Value of second is invalid" << e << endl;
    }
}

void earthquake::set_sec(string a){
    try
    {
        int b = str2int(a);
        set_sec(b);
    }
    catch (int e)
    {
        set_sec(-1);
    }
}

void earthquake::set_ms(double a) {
    try
    {
        if (a < 0 || a > 59)
            throw (22);
        else
            sec = a;
    }
    catch (int e)
    {
        cout << "Value of ms is invalid" << e << endl;
    }
}

void earthquake::set_ms(string a){
    try
    {
        int b = str2int(a);
        set_ms(b);
    }
    catch (int e)
    {
        set_ms(-1);
    }
}

// **************************** dt *****************************
bool isok_timezone(string str) {
    toupper_str(str);
    if (str == "PST" || str == "CST" || str == "EST" || str == "MST")
        return true;
    return false;
}

void earthquake::set_dt(string str2, ofstream & log)
{
    
    stringstream stro;
    string sdt, stm, stz;
    string syear, smnth, sday, shour, smin, ssec, sms;
    
    try {
        
        char str[50];
        strncpy(str, str2.c_str(), sizeof(str));
        str[sizeof(str)-1] = 0;
        
        replace(str, str + strlen(str), '/', ' ');
        replace(str, str + strlen(str), ':', ' ');
        
        std::vector<std::string> aln = split(str2, ' ');
        std::vector<std::string> adt = split(aln[0], '/');
        if (adt.size() != 3) throw (61);
        std::vector<std::string> atm = split(aln[1], ':');
        if (atm.size() != 3) throw (62);
        std::vector<std::string> asc = split(atm[2], '.');
        
        
        // date
        size_t n1 = adt.size();
        for (size_t i = 0; i < n1; i++)
        {
            size_t n2 = adt[i].size();
            for (size_t ii = 0; ii < n2; ii++)
            {
                if (!isdigit(adt[i][ii]))
                    throw (61);
                // there is an error
            }
        }
        sday = adt[1];
        syear = adt[2];
        
        
        //EQ.month = mnth_str2enum(adt[0]);
        set_month(adt[0]);
        //EQ.day = str2int(day);
        set_day(sday);
        //EQ.yr = str2int(year);
        set_year(syear);
        
        
        // time
        n1 = atm.size() - 1;
        for (size_t i = 0; i < n1; i++)
        {
            size_t n2 = atm[i].size();
            for (size_t ii = 0; ii < n2; ii++)
            {
                if (!isdigit(atm[i][ii]))
                    throw (62);
                // there is an error
            }
        }
        
        if (aln.size() != 3)
            throw (63);
        if (!isok_timezone(aln[2]))
            throw (63);
        
        shour = atm[0];
        smin = atm[1];
        ssec = asc[0];
        sms = asc[1];
        stz = aln[2];
        
        hr = str2int(shour);
        min = str2int(smin);
        sec = str2int(ssec);
        ms = str2int(sms);
        
    }
    catch (int e) {
        
        if (e == 61){
            stro << "Error! date is invalid" << endl;
            print(log, stro);
            exit(0);
        }
        
        if (e == 62){
            stro << "Error! time is invalid" << endl;
            print(log, stro);
            exit(0);
        }
        
        if (e == 63){
            stro << "Error! time zone is invalid" << endl;
            print(log, stro);
            exit(0);
        }
        
        stro << "Error! date / time is invalid" << endl;
        print(log, stro);
        exit(0);
    }
}

// **************************** END *****************************
//enum magnitude_type {
//    ML, Ms, Mb, Mw
//};
bool isok_magnitude(string str){
    toupper_str(str);
    if (str == "ML" || str == "MS" || str == "MB" || str == "MW")
        return true;
    return false;
}
const char *magnitude_type2str[] = { "ML", "Ms", "Mb", "Mw" };
int magnitude_Type_enum(string str) {
    
    toupper_str(str);
    
    if (str == "ML")
        return 0;
    if (str == "MS")
        return 1;
    if (str == "MB")
        return 2;
    if (str == "MW")
        return 3;
    
    return -1;
}

string earthquake::get_magnitude_Type_str() {
    return magnitude_type2str[magnitude_Type];
}

void earthquake::set_magnitude_Type(magnitude_type a) {
    try
    {
        magnitude_Type = a;
    }
    
    catch (int e)
    {
        cout << "Value of magnitude Type is invalid" << endl;
    }
}
void earthquake::set_magnitude_Type(string a) {
    try
    {
        set_magnitude_Type((magnitude_type)magnitude_Type_enum(a));
    }
    catch (int e)
    {
        cout << "Value of month is invalid" << endl;
    }
}




void earthquake::set_magnitude(double a) {
    try
    {
        if (a < 0 || a > 12)
            throw (22);
        else
            magnitude = a;
    }
    catch (int e)
    {
        cout << "Value of magnitude is invalid" << e << endl;
    }
}
void earthquake::set_magnitude(string a){
    try
    {
        int b = str2int(a);
        set_magnitude(b);
    }
    catch (int e)
    {
        set_magnitude(-1);
    }
}

void earthquake::set_lon(double a) {
    try
    {
        if (a < -180 || a > +180)
            throw (22);
        else
            lon = a;
    }
    catch (int e)
    {
        cout << "Value of lon is invalid" << e << endl;
    }
}
void earthquake::set_lon(string a){
    try
    {
        int b = str2int(a);
        set_lon(b);
    }
    catch (int e)
    {
        set_lon(-1);
    }
}

void earthquake::set_lat(double a) {
    try
    {
        if (a < -90 || a > 90)
            throw (22);
        else
            lat = a;
    }
    catch (int e)
    {
        cout << "Value of lat is invalid" << e << endl;
    }
}
void earthquake::set_lat(string a){
    try
    {
        int b = str2int(a);
        set_lat(b);
    }
    catch (int e)
    {
        set_lat(-1);
    }
}

void earthquake::set_elv(double a) {
    try
    {
        if (a < 0 || a > 100000)
            throw (22);
        else
            elv = a;
    }
    catch (int e)
    {
        cout << "Value of elv is invalid" << e << endl;
    }
}
void earthquake::set_elv(string a){
    try
    {
        int b = str2int(a);
        set_elv(b);
    }
    catch (int e)
    {
        set_elv(-1);
    }
}




bool isok_magnitude_size(double magnitude) {
    if (magnitude <= 0)
        return false;
    return true;
}
void earthquake::set_mag(string lm, ofstream & log){
    
    // Fourth row: epicenter location (three doubles: longitude, latitude, and
    // depth), followed by magnitude type and magnitude size (a string and a
    // float, respectively). e.g. -115.66 31.53 0.9 mw 4.9
    
    char* pEnd;
    stringstream str;
    string longitude, latitude, elevation, geo, magnitude_type, magnitude_size;
    double fmagnitude_size;
    
    //istringstream is not standard/not compatible with mingw
    
    std::vector<std::string> astr = split(lm, ' ');
    
    longitude = astr[0];
    latitude = astr[1];
    elevation = astr[2];
    magnitude_type = astr[3];
    magnitude_size = astr[4];
    
    char cmagnitude_size[50];
    strcpy(cmagnitude_size, magnitude_size.c_str());
    
    fmagnitude_size = std::strtod(cmagnitude_size, &pEnd);
    if (!isok_magnitude(magnitude_type))
    {
        str << "Error! Magnitude type is invalid" << endl;
        print(log, str);
        exit(0);
    }
    set_magnitude(fmagnitude_size);
    set_magnitude_Type(magnitude_type);
    
    char clongitude[10], clatitude[10], celevation[10];
    
    strcpy(clongitude, longitude.c_str());
    strcpy(clatitude, latitude.c_str());
    strcpy(celevation, elevation.c_str());
    
    set_lon(std::strtod(clongitude, &pEnd));
    set_lat(std::strtod(clatitude, &pEnd));
    set_elv(std::strtod(celevation, &pEnd));
    
    if (!isok_magnitude_size(fmagnitude_size))
    {
        str << "Error! Magnitude must be real positive" << endl;
        print(log, str);
        exit(0);
    }
}

// ********** general functions (put them on a seperate file?) ****************

void toupper_str(std::string& str) {
    
    for (size_t i = 0; i < str.size(); ++i)
        str[i] = toupper(str[i]);
    
}

string toupper_str_C(std::string str) {
    
    toupper_str(str);
    
    return str;
}

std::vector<std::string> &split(const std::string &s, char delim,
                                std::vector<std::string> &elems) {
    
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    
    std::vector<std::string> elems;
    split(s, delim, elems);
    
    return elems;
}

void print(ofstream & o, stringstream & txt, bool only2file) {
    
    std::cout.precision(3);
    o.precision(3);
    
    if (!only2file) cout << txt.str();
    
    o << txt.str();
    
    txt.str(std::string());
    txt.clear();
}

