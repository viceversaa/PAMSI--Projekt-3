#pragma once
struct field
{
    int x, y;
    field(char x, int y) : x(x - 'a'), y(y - 1){}

    field(int x, int y) : x(x), y(y){}
};
ostream &operator<<(ostream &str, const field &field)
{
    str << char(field.x + 'a') << field.y + 1;
    return str;
}
