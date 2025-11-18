// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

wchar_t s[] = L"\u2722";

