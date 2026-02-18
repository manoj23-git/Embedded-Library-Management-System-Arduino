#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <EEPROM.h>

#define MAX_BOOKS 5
#define COUNT_ADDR 0   // EEPROM address for book count

LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ---------- Keypad ---------- */
const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

/* ---------- Structure ---------- */
struct Book {
  char title[10];
  char author[10];
  int year;
};

/* ---------- EEPROM helpers ---------- */
int getCount() {
  return EEPROM.read(COUNT_ADDR);
}

void setCount(int c) {
  EEPROM.write(COUNT_ADDR, c);
}

void saveBook(int index, Book b) {
  EEPROM.put(1 + index * sizeof(Book), b);
}

Book readBook(int index) {
  Book b;
  EEPROM.get(1 + index * sizeof(Book), b);
  return b;
}

/* ---------- Input ---------- */
void readString(char *buf, int len) {
  int i = 0;
  while (i < len - 1) {
    char k = keypad.getKey();
    if (k) {
      if (k == '#') break;
      buf[i++] = k;
      lcd.print(k);
    }
  }
  buf[i] = '\0';
}

/* ---------- Add ---------- */
void addBook() {
  int count = getCount();
  if (count >= MAX_BOOKS) {
    lcd.clear(); lcd.print("Memory Full");
    delay(5000); return;
  }

  Book b;

  lcd.clear(); lcd.print("Title:");
  lcd.setCursor(0,1); readString(b.title,10);

  lcd.clear(); lcd.print("Author:");
  lcd.setCursor(0,1); readString(b.author,10);

  lcd.clear(); lcd.print("Year:");
  lcd.setCursor(0,1);
  char y[5]; readString(y,5);
  b.year = atoi(y);

  saveBook(count, b);
  setCount(count + 1);

  lcd.clear(); lcd.print("Saved!");
  delay(5000);
}
/* ---------- View with navigation ---------- */
void viewBooks() {
  int count = getCount();
  if (count == 0) {
    lcd.clear(); lcd.print("No Books");
    delay(2000);
    return;
  }
  int i = 0;
  while (1) {
    Book b = readBook(i);

    lcd.clear();
    lcd.print(b.title);
    lcd.setCursor(0,1);
    lcd.print(b.year);

    unsigned long start = millis();

    // wait up to 2 seconds while checking keypad continuously
    while (millis() - start < 2000) {
      char k = keypad.getKey();

      if (k == 'A') {          // NEXT
        i = (i + 1) % count;
        break;
      }
      else if (k == 'B') {     // PREVIOUS
        i = (i - 1 + count) % count;
        break;
      }
      else if (k == '*') {     // EXIT
        lcd.clear();
        return;
      }
    }
  }
}
/* ---------- Delete last ---------- */
void deleteBook() {
  int count = getCount();
  if (count == 0) {
    lcd.clear(); lcd.print("Nothing Del");
    delay(5000); return;
  }

  setCount(count - 1);
  lcd.clear(); lcd.print("Deleted");
  delay(5000);
}

/* ---------- Search by title ---------- */
void searchBook() {
  int count = getCount();
  if (count == 0) {
    lcd.clear(); lcd.print("No Books");
    delay(5000); return;
  }

  char keyTitle[10];
  lcd.clear(); lcd.print("Search:");
  lcd.setCursor(0,1); readString(keyTitle,10);

  for (int i = 0; i < count; i++) {
    Book b = readBook(i);
    if (strcmp(b.title, keyTitle) == 0) {
      lcd.clear(); lcd.print(b.title);
      lcd.setCursor(0,1); lcd.print(b.author);
      delay(8000); return;
    }
  }

  lcd.clear(); lcd.print("Not Found");
  delay(5000);
}

/* ---------- Setup ---------- */
void setup() {
  lcd.init();
  lcd.backlight();

  if (getCount() > MAX_BOOKS) setCount(0);

  lcd.print("Embedded Lib");
  delay(5000);
}

/* ---------- Loop ---------- */
void loop() {
  lcd.clear();
  lcd.print("1A 2V 3D 4S");

  char k = keypad.getKey();

  if (k == '1') addBook();
  else if (k == '2') viewBooks();
  else if (k == '3') deleteBook();
  else if (k == '4') searchBook();
}
