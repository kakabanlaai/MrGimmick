#pragma once

class MiniBossState;
class MiniBoss;

class MiniBossData
{
public:
	MiniBossData();
	~MiniBossData();

	MiniBoss* miniBoss;
	MiniBossState* state;
protected:

};

