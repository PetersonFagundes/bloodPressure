#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <exception>

class Pressure {

private:
	// Systolic pressures.
	int systolic;
	// Diastolic pressures.
	int diastolic;

    // Systolic pressures.
	int systolicL;
	// Diastolic pressures.
	int diastolicL;

	// Vector with arterial blood pressure wave.
	std::vector<int> bloodPressure;

	// Vector with local max.
	std::vector<int> localMax;

	//Vector with local min.
	std::vector<int> localMin;

	int m_size;

	int* m_position;

public:
	// Contructor.
	Pressure();

	// Find the systolic / diastolic pressure.
	void Pressures(int* position, int size, int index);

	// Return systolic pressure.
	int GetSystolic();

	// Return diastolic pressure.
	int GetDiastolic();

	// Destructor
	~Pressure();

private:

	// Read the data.
	void LerDados(int* position, int size);

    // Find max and notch.
	// Save indexs.
	void FindLocalMaxMin();

	void MaxLocal();

	void MinLocal();

    bool IsPositiveFalse(int nIndex);

    bool IsPositiveFalseDiastolicPresure(int nIndex);

	// Find systolic pressure.
	int SystolicPressure(int index, int nLado);

	// Find diastolic pressure.
	int DiastolicPresure(int index, int nLado);

    int RealValueDiastolic(int index, int diastolicLeft, int diastolicRight);

    int RealValueSystolic(int index, int systolicLeft, int systolicRight);
};

