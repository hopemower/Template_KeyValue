#ifndef CARTON_H
#define CARTON_H

#include <iostream>

class Carton {

public:
    // constructors and destructor
    Carton();
    Carton(float length, float width, float height);
    ~Carton() {}

    // getters
    float GetLength() const { return length_; }
    float GetWidth() const { return width_; }
    float GetHeight() const { return height_; }

    // setters
    void SetLength(float length);
    void SetWidth(float width);
    void SetHeight(float height);

    // other methods
    float Volume() const;
    void WriteData(std::ostream &out) const;
    void WriteCarton(std::ostream &out) const;
    bool operator == (const Carton &rhs) const;
    friend std::ostream& operator<< (std::ostream& out, const Carton& rhs);


private:
    float length_;
    float width_;
    float height_;
};

#endif