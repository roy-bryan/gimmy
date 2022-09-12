
class Byte {
private:
	char byte;             // 0 to infinite

public:
	// required constructors
	Byte() {
	 byte = (char) 0;
	}
	Byte(int f) {
	 byte = (char) f;
	}
	
	int getNum() {
		return (int) byte;
	}
	
	void operator=(const Byte &D ){ 
		byte = D.byte;
	}
	void operator=(const int d ){ 
		byte = (char) d;
	}
	void operator=(const char c){
		byte = c;
	}
	
	Byte operator<<(const int d ){ 
		Byte val = byte << d;
		return val;
	}
	
	Byte operator>>(const int d ){ 
		Byte val = byte >> d;
		return val;
	}
	
	Byte operator&(const Byte &D){
		Byte val = byte & D.byte;
		return val;
	}
	
	Byte operator&(const int d){
		Byte val = byte & (char) d;
		return val;
	}
	
	Byte operator|(const Byte &D){
		Byte val = byte | D.byte;
		return val;
	}
	
	Byte operator|(const int d){
		Byte val = byte | (char) d;
		return val;
	}
	
	Byte operator^(const Byte &D){
		Byte val = byte ^ D.byte;
		return val;
	}
	
	Byte operator^(const int d){
		Byte val = byte ^ (char) d;
		return val;
	}
	
	Byte operator+(const Byte &D){
		Byte val = byte + D.byte;
		return val;
	}
	
	Byte operator-(const Byte &D){
		Byte val = byte - D.byte;
		return val;
	}
	
	Byte operator*(const Byte &D){
		Byte val = byte * D.byte;
		return val;
	}
	
	bool operator==(const Byte &D){
		return byte == D.byte;
	}
	
	bool operator==(const int i){
		return byte == (char) i;
	}
	
	bool operator!=(const int i){
		return !(operator==(i));
	}
	
	bool operator!=(const Byte &D){
		return !(operator==(D));
	}
};
