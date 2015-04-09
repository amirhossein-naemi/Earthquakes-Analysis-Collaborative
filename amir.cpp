//-----------------------------------------------------------------------------
//
// Earthquakes' Events Analysis
// By Amirhossein Naemi
// March, 2015
// GIT: https://github.com/amirhossein-naemi/Earthquakes-Analysis-v3
//
//-----------------------------------------------------------------------------

#include "earthquake.h"
#include "station.h"
#include <iomanip>
#include <sstream>

using namespace std;
earthquake EQ;
const int  MAXDATA = 300;
station    stations[MAXDATA];
int valid, invalid, sign;

void open_input(ifstream & ifile, string ifilename, ofstream & log) {
    // Sanity check on the file stream
    
    ifile.open(ifilename.c_str());
    if (!ifile.is_open()) {
        stringstream str;
        str << "Error! Cannot open input file: " << ifilename << endl;
        print(log, str);
        exit(0);
    }
    
    return;
}

void open_output(ofstream & o, string ofilename) {
    
    // Print on output file
    o.open(ofilename.c_str());
    if (!o.is_open()) {
        cout << "Error! The output file: " + ofilename + " is locked\n";
        exit(0);
    }
    
    return;
}

void read_header(ifstream & in, ofstream & log) {
    
    string lID, ldt, lnam, lm, eID, ID, dt, nam, geo, tm, tz, magnitude_type;
    stringstream str;
    
    std::getline(in, lID);
    std::getline(in, ldt);
    std::getline(in, lnam);
    std::getline(in, lm);
    
    EQ.set_dt(ldt, log);
    EQ.set_mag(lm, log);
    
    str << eID << endl;
    print(log, str);
    str.clear();

    EQ.earthquake_name = lnam;
    EQ.id = lID;

    str << lnam << endl;
    print(log, str, true);
}

void read_data(ifstream & in, ofstream & out, ofstream & log) {
    
    stringstream str;
    string eqnet, eqst, eqbnd, eqins, eqor;
    station   eqtmp;
    int  cnt = 0, i = 0;
    bool noerr;
    
    while (in >> eqnet) {
        cnt++;
        noerr = true;
        try
        {
            in >> eqst >> eqbnd >> eqins >> eqor;
            
            if (!eqtmp.set_network_code(eqnet))
            {
                noerr = false;
                str << "Entry # " << setw(3) << right << cnt
                << " ignored. Invalid network.\n";
                print(log, str);
            }
            
            if (!eqtmp.set_station_name(eqst))
            {
                noerr = false;
                str << "Entry # " << setw(3) << right << cnt
                << " ignored. Invalid station name.\n";
                print(log, str);
            }
            
            if (!eqtmp.set_type_of_band(eqbnd))
            {
                noerr = false;
                str << "Entry # " << setw(3) << cnt
                << " ignored. Invalid band type.\n";
                print(log, str);
            }
            
            if (!eqtmp.set_type_of_instrument(eqins))
            {
                noerr = false;
                str << "Entry # " << setw(3) << cnt
                << " ignored. Invalid instrument.\n";
                print(log, str);
            }
            
            if (!eqtmp.set_orientation(eqor))
            {
                noerr = false;
                str << "Entry # " << setw(3) << cnt
                << " ignored. Invalid Orientation.\n";
                print(log, str);
            }
            
            if (is_there_any_err(eqtmp))
                throw (30);
        }
        catch (int e)
        {
            // any other errors
            noerr = false;
            cout << "An exception occurred. Exception Nr. " << e << '\n';
        }

        if (noerr) {
            stations[i] = eqtmp;
            i++;
        }
    }
    
    invalid = cnt - i;
    valid = i;
    if (valid < 1) {
        str << "logor! input number should be equal or greater than 1\n";
        print(log, str);
        exit(0);
    }
}

void process(ifstream & ifile, ofstream & log){
    
    double el = EQ.get_lon();
    stringstream str, str2;
    str.precision(3);
    str << "# " << EQ.get_day() << " " << EQ.get_month_str() << " "
    << EQ.get_year() << " " << setfill('0') << setw(2) << EQ.get_hour()
    << ":" << setfill('0') << setw(2) << EQ.get_min() << ":" << setfill('0')
    << setw(2) << EQ.get_sec() << '.' << setfill('0') << setw(3)
    << std::setprecision(0) << std::fixed << EQ.get_ms() << " " << EQ.tz
    << " " << EQ.get_magnitude_Type_str() << " " << std::fixed
    << std::setprecision(1) << EQ.get_magnitude() << " "
    << EQ.earthquake_name << " [" << EQ.id << "] (" << std::setprecision(2)
    << std::fixed << EQ.get_lon() << ", " << std::fixed << EQ.get_lat()
    << ", " << std::setprecision(1) << EQ.get_elv() << ")" << endl;
    
    sign = 0;
    
    for (int i = 0; i < valid; i++) {
        string s = stations[i].get_orientation();
        int n = s.size();
        for (size_t j = 0; j < n; j++) {
            
            str2 << EQ.id << '.'
            << stations[i].get_network_code_str() << '.'
            << stations[i].get_station_name() << '.'
            << stations[i].get_type_of_band_str()
            << stations[i].get_type_of_instrument_str()
            << s[j] << endl;
            
            sign++;
        }
    }
    
    str << sign << endl;
    
    print(log, str, true);
    
    print(log, str2, true);
}

int main() {
    
    string       inputfilename;
    ofstream     log, out;
    ifstream     in;
    stringstream str;
    
    open_output(log, "amir.log");
    
    // Prompt user for input/output file
    cout << "Enter input file: ";
    cin >> inputfilename;
    
    // sample data for testing purposes
    // inputfilename = "amir.in";
    
    str << endl << "Opening file: " << inputfilename << endl;
    open_input(in, inputfilename, log);
    
    str << "Processing input..." << endl;
    print(log, str);
    
    read_header(in, log);
    
    str << "Header read correctly!" << endl << endl;
    print(log, str);
    
    open_output(out, "amir.out");
    
    read_data(in, out, log);
    process(in, out);
    print(out, str);
    
    str << endl << "Total invalid entries ignored: " << setw(2) << invalid
        << endl << "Total valid entries read: "      << setw(7) << valid 
        << endl << "Total signals produced: "        << setw(9) << sign << endl;
    
    print(log, str);
    
    if (log.is_open())
        log.close();
    if (in.is_open())
        in.close();
    if (out.is_open())
        out.close();
    
    return 0;
}

