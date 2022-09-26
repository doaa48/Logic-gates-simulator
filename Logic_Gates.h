
enum STATUS
{
    LOW,
    HIGH
};

enum Gates_Type
{
    AND,
    OR,
    NAND,
    NOR,
    XOR,
    XNOR,
    NOT
};

/*========================================= Node Class =====================================*/

class Node
{
private:
    STATUS m_Status;
    char Node_Name;
public:
    Node();
    Node( STATUS Status,char NodeName);
    void setNodeStatus(STATUS r_Status);
    void setNodeName(char Node_Node_p);
    STATUS getNodeStatus();
    char getNodeName();
    friend ostream& operator<<(ostream& out, const Node & node)
    {
        out <<node.Node_Name  << ": "<<node.m_Status<< endl;
        return out;
    }
    static STATUS OR_Operate (STATUS Node1_Stat,STATUS Node2_Stat);
    static STATUS AND_Operate(STATUS Node1_Stat,STATUS Node2_Stat);
    static STATUS XOR_Operate(STATUS Node1_Stat,STATUS Node2_Stat);


};


/*========================================= Gate Class =====================================*/


class Gate
{
protected:
    Node Input1_Node;
    Node Input2_Node;
    Node Output_Node;
    Gates_Type Type;

public:
    Gate();
    Gate(Node Input1_Node_p, Node Input2_Node_p,Node Output_Node_p);
    void setGateInput1Name(char Name );
    void setGateInput2Name(char Name );
    void setGateOutputName(char Name );

    void setGateInput1Status(STATUS Stat );
    void setGateInput2Status(STATUS Stat  );
    void setGateOutputStatus(STATUS Stat);
    void setGateType(Gates_Type GateType);

    virtual char GetGateInput1Name();
    virtual char GetGateInput2Name();
    virtual char GetGateOutputName();
    virtual STATUS GetGateInput1Status();
    virtual STATUS GetGateInput2Status();
    virtual STATUS GetGateOutputStatus();
    Gates_Type GetGateTypeStatus( );
    virtual void simulateGate(int iterator);


};

/*========================================= Simulator Class =====================================*/

class Simulator
{

public:

    Simulator();
    static int GatesCounter;
    static int NodesCounter;
    static int TypeNum;
    static Gate GatesArr[500];
    static Node NodesArr[500];
    static int FinalOutput_Index;
    static void postGate(const Gate & obj );
    static void postNode(const Node & obj);
    static signed int FindNode( char Node_name);
    static void startSimulate();
    static Gates_Type FindType(string line);
    static void Print();
    static void SetAllNodes(char Name,STATUS stat);


};

/*========================================= Generator Class =====================================*/

class GateGenerator
{
    string InputStrings[30];
public:
    GateGenerator();
    void  parseInput();
    void  createNode(Node node);
    void  createGate(string Line );

};

/*=============================================================================================*/
