// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int test(int val){
	int x = 12;
	switch (val) {
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

int main(void) {
  return test(4);
}
