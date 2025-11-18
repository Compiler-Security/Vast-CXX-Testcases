// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int main(void){
	int x = 12;
	switch (4) {
		case 4: do { 
                     switch (6)  {
                       case 6: {
                         case 5: x++;
                       };
                     };
                } while (x < 100);
	}
	return x;
}
