#include <lfpRatiometer>

int main() {

    // instantiate an object
    int N = 10;
    double sampling = 200;
    lfpRatiometer lfpratiometer(N, sampling);
    std::cout << "####### Calculation #1 #######\n";
    std::cout << "The sampling rate is " << sampling << "Hz.\n";

    // define a time series for the calculation
    std::vector<double> in_raw;
    for (int j=0; j<N; j++) {
        in_raw.push_back(1);
    }
    in_raw.at(1) = 2;
    in_raw.at(4) = 3;
    in_raw.at(8) = 2;
    lfpratiometer.setTimeSeries(in_raw);
    std::vector<double> buffer_curr = lfpratiometer.getBuffer();
    std::cout << "Time buffer actually is [";
    for (int i=0; i<buffer_curr.size(); i++) {
        std::cout << buffer_curr.at(i) << ' ';
    }
    std::cout << "].\n\n";

    // calculating FFT magnitudes
    lfpratiometer.makeFFTabs();
    std::vector<double> fftabs_curr = lfpratiometer.getFFTabs();
    std::vector<double> freqvec_curr = lfpratiometer.getFreqs();

    std::cout << "The frequency vector is [";
    for (int i=0; i<freqvec_curr.size(); i++) {
        std::cout << freqvec_curr.at(i) << ' ';
    }
    std::cout << "].\n";
    std::cout << "Calculated |FFT| with a rectangular window is [";
    for (int i=0; i<fftabs_curr.size(); i++) {
        std::cout << fftabs_curr.at(i) << ' ';
    }
    std::cout << "].\n";
    std::cout << "Compare these results with MATLAB's output using '[s,f,~]=spectrogram(test_vec,ones(size(test_vec)),0,length(test_vec),Fs)' and 'abs(s)'.\n";
    std::cout << "Also can compare with MATLAB's 'abs(fft(test_vec))'.\n\n";

    // ANOTHER CALCULATION

    // instantiate an object
    N = 11;
    sampling = 150;
    lfpratiometer.changeFFTPlan(N,sampling);
    std::cout << "####### Calculation #2 #######\n";

    std::cout << "The sampling rate is " << sampling << "Hz.\n";

    // define a time series for the calculation
    in_raw.clear();
    for (int j=0; j<N; j++) {
        in_raw.push_back(1);
    }
    in_raw.at(1) = 2;
    in_raw.at(8) = 3;
    in_raw.at(10) = 2;
    lfpratiometer.setTimeSeries(in_raw);
    buffer_curr = lfpratiometer.getBuffer();
    std::cout << "Time buffer actually is [";
    for (int i=0; i<buffer_curr.size(); i++) {
        std::cout << buffer_curr.at(i) << ' ';
    }
    std::cout << "].\n\n";

    // calculating FFT magnitudes
    lfpratiometer.window_hamming();
    lfpratiometer.makeFFTabs();
    fftabs_curr = lfpratiometer.getFFTabs();
    freqvec_curr = lfpratiometer.getFreqs();

    std::cout << "The frequency vector is [";
    for (int i=0; i<freqvec_curr.size(); i++) {
        std::cout << freqvec_curr.at(i) << ' ';
    }
    std::cout << "].\n";
    std::cout << "Calculated |FFT| with a Hamming window is [";
    for (int i=0; i<fftabs_curr.size(); i++) {
        std::cout << fftabs_curr.at(i) << ' ';
    }
    std::cout << "].\n";
    std::cout << "Compare these results with MATLAB's output using '[s,f,~]=spectrogram(test_vec,hamming(length(test_vec)),0,length(test_vec),Fs)' and 'abs(s)'.\n";
    std::cout << "Also can compare with MATLAB's 'abs(fft(test_vec.*hamming(length(test_vec))'))'.\n\n";

    return 0;
}