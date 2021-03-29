extern "C" int _printik(const char*, ...);


int main() {
    
    int number = 30;
    int eda = 3802;
    char love[] = {"love"};
    char I = 73;

    _printik("%c %s %h for %d%%!%b", I, love, eda, number, 255);
    _printik("%c %s %h for %d%%%c%b", 'I', "love", 0xEDA, 30, 33, 255);
    
    return 0;
}
