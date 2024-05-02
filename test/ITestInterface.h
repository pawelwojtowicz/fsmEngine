#ifndef ITESTINTERFACE_H
#define ITESTINTERFACE_H

class ITestInterface
{
public:
	ITestInterface() {};
	virtual ~ITestInterface() {};
	
public:
	virtual void OperationA() = 0;
	virtual void OperationB() = 0;
	virtual void OperationC() = 0;
	virtual void OperationD() = 0;
	virtual void OperationE() = 0;
	virtual void OperationF() = 0;
	virtual void OperationG() = 0;
	virtual void OperationH() = 0;
	
	virtual bool Condition1() = 0;
	virtual bool Condition2() = 0;
	virtual bool Condition3() = 0;
	virtual bool Condition4() = 0;
	virtual bool Condition5() = 0;
	virtual bool Condition6() = 0;
	virtual bool Condition7() = 0;
	virtual bool Condition8() = 0;
	
private:
	ITestInterface(const ITestInterface&);
	ITestInterface& operator= ( const ITestInterface&);
};

class TestOperationsMock : public ITestInterface
{
public:
	MOCK_METHOD0( OperationA , void () );
	MOCK_METHOD0( OperationB , void () );
	MOCK_METHOD0( OperationC , void () );
	MOCK_METHOD0( OperationD , void () );
	MOCK_METHOD0( OperationE , void () );
	MOCK_METHOD0( OperationF , void () );
	MOCK_METHOD0( OperationG , void () );
	MOCK_METHOD0( OperationH , void () );
	
	MOCK_METHOD0( Condition1 , bool () );
	MOCK_METHOD0( Condition2 , bool () );
	MOCK_METHOD0( Condition3 , bool () );
	MOCK_METHOD0( Condition4 , bool () );
	MOCK_METHOD0( Condition5 , bool () );
	MOCK_METHOD0( Condition6 , bool () );
	MOCK_METHOD0( Condition7 , bool () );
	MOCK_METHOD0( Condition8 , bool () );
};

#endif
