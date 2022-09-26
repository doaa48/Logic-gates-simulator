#include <iostream>
using namespace std;
#include "string"
#include "Logic_Gates.h"

/*========================================= Node Functions =====================================*/

Node::Node()
{
    m_Status = LOW;	//Default Status is LOW
    Node_Name= 0;
}
Node ::Node( STATUS Status,char NodeName):m_Status(Status),Node_Name(NodeName)
{
}
void Node::setNodeStatus(STATUS r_Status)
{
    m_Status = r_Status;
}
void Node::setNodeName(char Node_Name_p)
{
    Node_Name = Node_Name_p;
}

STATUS Node::getNodeStatus()
{
    return m_Status;
}
char Node::getNodeName()
{
    return Node_Name;
}


STATUS Node:: OR_Operate(STATUS Node1_Stat,STATUS Node2_Stat)
{
    if (Node1_Stat == HIGH || Node2_Stat ==HIGH)
        return HIGH;
    else
        return LOW;
}

STATUS Node::AND_Operate(STATUS Node1_Stat,STATUS Node2_Stat)
{
    if (Node1_Stat == LOW || Node2_Stat ==LOW)
        return LOW;
    else
        return HIGH;
}
STATUS Node::XOR_Operate(STATUS Node1_Stat,STATUS Node2_Stat)
{
    if (Node1_Stat == Node2_Stat)
        return LOW;
    else
        return HIGH;

}



/*========================================= Gate Functions =====================================*/


Gate ::Gate()
{
}

Gate ::Gate(Node Input1_Node_p, Node Input2_Node_p,Node Output_Node_p):Input1_Node(Input1_Node_p),Input2_Node(Input2_Node_p),Output_Node(Output_Node_p)
{

}

void Gate :: setGateInput1Name(char Name )
{
    Input1_Node.setNodeName(Name);
}
void Gate ::setGateInput2Name(char Name )
{
    Input2_Node.setNodeName(Name);
}
void Gate ::setGateOutputName(char Name )
{
    Output_Node.setNodeName(Name);
}

void Gate ::setGateInput1Status(STATUS Stat )
{
    Input1_Node.setNodeStatus(Stat);
}
void Gate ::setGateInput2Status(STATUS Stat  )
{
    Input2_Node.setNodeStatus(Stat);
}
void Gate ::setGateOutputStatus(STATUS Stat)
{
    Output_Node.setNodeStatus(Stat);
}
void Gate ::setGateType(Gates_Type GateType)
{
    Type= GateType;
}
char Gate:: GetGateInput1Name()
{
    return Input1_Node.getNodeName();
}
char Gate::GetGateInput2Name()
{
    return Input2_Node.getNodeName();
}
char Gate::GetGateOutputName()
{
    return Output_Node.getNodeName();

}
STATUS Gate::GetGateInput1Status( )
{
    return Input1_Node.getNodeStatus();
}
STATUS Gate::GetGateInput2Status()
{
    return Input2_Node.getNodeStatus();
}
STATUS Gate:: GetGateOutputStatus( )
{
    return Output_Node.getNodeStatus();
}
Gates_Type Gate:: GetGateTypeStatus( )
{
    return Type;
}
void Gate:: simulateGate(int iterator)
{
    if(Type==OR)
    {
        if (Input1_Node.getNodeStatus() == HIGH || Input2_Node.getNodeStatus() ==HIGH)
        {
            Output_Node.setNodeStatus(HIGH);
            Simulator::SetAllNodes( Output_Node.getNodeName(),HIGH);
        }
        else
        {
            Output_Node.setNodeStatus(LOW);
            Simulator::SetAllNodes( Output_Node.getNodeName(),LOW);

        }
    }
    else if(Type == AND)
    {
        if (Input1_Node.getNodeStatus() == LOW || Input2_Node.getNodeStatus() ==LOW)
        {
            Output_Node.setNodeStatus(LOW);
            Simulator::SetAllNodes( Output_Node.getNodeName(),LOW);

        }
        else
        {
            Output_Node.setNodeStatus(HIGH);
            Simulator::SetAllNodes( Output_Node.getNodeName(),HIGH);
        }

    }
    else if(Type == NAND)
    {
        if (Input1_Node.getNodeStatus() == LOW || Input2_Node.getNodeStatus() ==LOW)
        {
            Output_Node.setNodeStatus(HIGH);
            Simulator::SetAllNodes( Output_Node.getNodeName(),HIGH);
        }
        else
        {
            Output_Node.setNodeStatus(LOW);
            Simulator::SetAllNodes( Output_Node.getNodeName(),LOW);

        }
    }
    else if(Type == NOR) {
        if (Input1_Node.getNodeStatus() == HIGH || Input2_Node.getNodeStatus() == HIGH)
        {
            Output_Node.setNodeStatus(LOW);
            Simulator::SetAllNodes( Output_Node.getNodeName(),LOW);

        }
        else {
            Output_Node.setNodeStatus(HIGH);
            Simulator::SetAllNodes(Output_Node.getNodeName(), HIGH);
        }
    }
    else if(Type == XOR)
    {
        if (Input1_Node.getNodeStatus() == Input2_Node.getNodeStatus())
        {
            Output_Node.setNodeStatus(LOW);
            Simulator::SetAllNodes( Output_Node.getNodeName(),LOW);

        }
        else
        {
            Output_Node.setNodeStatus(HIGH);
            Simulator::SetAllNodes( Output_Node.getNodeName(),HIGH);
        }
    }
    else if(Type == XNOR)
    {
        if (Input1_Node.getNodeStatus() == Input2_Node.getNodeStatus())
        {
            Output_Node.setNodeStatus(HIGH);
            Simulator::SetAllNodes( Output_Node.getNodeName(),HIGH);
        }
        else
        {
            Output_Node.setNodeStatus(LOW);
            Simulator::SetAllNodes( Output_Node.getNodeName(),LOW);

        }
    }
    else if(Type == NOT)
    {
        if (Input1_Node.getNodeStatus() == LOW)
        {
            Output_Node.setNodeStatus(HIGH);
            Simulator::SetAllNodes( Output_Node.getNodeName(),HIGH);

        }
        else
        {
            Output_Node.setNodeStatus(LOW);
            Simulator::SetAllNodes( Output_Node.getNodeName(),LOW);

        }
    }
}


/*========================================= Simulators Functions =====================================*/


int Simulator:: TypeNum=0;
int Simulator:: GatesCounter=0;
int Simulator:: NodesCounter=0;
int Simulator:: FinalOutput_Index=-1;
Gate Simulator::GatesArr[]={ Gate(Node(LOW,'\0'),Node(LOW,'\0'),Node(LOW,'\0')) };
Node Simulator::NodesArr[]={Node(LOW,'\0')};

Simulator::Simulator()
{

}
void Simulator::  postGate(const Gate & obj )
{
    GatesArr[GatesCounter]=obj;
    GatesCounter++;
}
void Simulator:: postNode(const Node & obj)
{
    NodesArr[NodesCounter]=obj;
    NodesCounter++;
}
signed int Simulator::FindNode( char Node_name)
{
    signed int i;
    for(i=0;i<NodesCounter;i++)
    {
        if(NodesArr[i].getNodeName()==Node_name)
        {
            return i;
        }
    }

    return -1;
}
void Simulator:: startSimulate()
{
    for (int i = 0; i < GatesCounter; ++i)
    {
        GatesArr[i].simulateGate(i);
    }

    Simulator::Print();
}

Gates_Type Simulator::FindType(string line)
{
    if(line[0]=='X')
    {
        if(line[1]=='N')
        {
            TypeNum=4;
            return XNOR;
        } else
        {   TypeNum=3;
            return XOR;
        }
    }
    else if(line[0]=='O')
    {
        TypeNum=2;
        return OR;
    }
    else if(line[0]=='A')
    {
        TypeNum=3;
        return AND;
    }
    else if(line[0]=='N')
    {
        if(line[1]=='A')
        {
            TypeNum=4;
            return NAND;
        }
        else if(line[2]=='R')
        {
            TypeNum=3;
            return NOR;
        }
        else
        {
            TypeNum=3;
            return NOT;
        }

    }
    return OR;
}

void Simulator::Print()
{
    cout<<NodesArr[FinalOutput_Index];
    for (int i = 0; i <NodesCounter ; ++i)
    {
        cout<<NodesArr[i];
    }
}

void Simulator:: SetAllNodes(char Name,STATUS stat)
{
    for (int i = 0; i <GatesCounter ; ++i)
    {
        if(Name==GatesArr[i].GetGateInput1Name())
        {
            GatesArr[i].setGateInput1Status(stat);
        }
        if(Name==GatesArr[i].GetGateInput2Name())
        {
            GatesArr[i].setGateInput2Status(stat);
        }
        if(Name==GatesArr[i].GetGateOutputName())
        {
            GatesArr[i].setGateOutputStatus(stat);
        }

    }
    for (int i = 0; i < NodesCounter; ++i)
    {
        if(Name==NodesArr[i].getNodeName())
        {
            NodesArr[i].setNodeStatus(stat);
        }
    }
}

/*========================================= Generator Functions =====================================*/

GateGenerator::GateGenerator()
{

}

void GateGenerator::parseInput()
{
    int i;
    int status=0;
    for( i=0;status==0;i++)
    {
        getline (cin,InputStrings[i]);

        if(InputStrings[i][1]=='U')
        {
            status=1;
        }
    }

    i=0;

    while(InputStrings[i][1]!='U')
    {
        if(InputStrings[i][0]!='S')
        {
            createGate(InputStrings[i]);
        }
        else if(InputStrings[i][0]=='S')
        {
            if(InputStrings[i][1]=='E')
            {

                if(InputStrings[i][6]=='0')
                {
                    Simulator::SetAllNodes(InputStrings[i][4],LOW);
                }
                else
                {
                    Simulator::SetAllNodes(InputStrings[i][4],HIGH);

                }

            }
            else
            {
                Simulator::FinalOutput_Index=Simulator::FindNode(InputStrings[i+1][4]);
                Simulator::startSimulate();
            }
        }

        i++;
    }



}
void GateGenerator :: createNode(Node node)
{
    Simulator::postNode(node);
}
void  GateGenerator::createGate(string Line )
{   int NOT_State=0;
    Gate GateObject;
    char SelectedChar;

    GateObject.setGateType(Simulator::FindType(Line));

    if(Simulator::FindType(Line) == NOT)
    {
        NOT_State=1;
    }
    SelectedChar=Line[Simulator::TypeNum+1];
    if(Simulator::FindNode(SelectedChar)== -1)
    {
        Node OB(LOW,SelectedChar);
        GateObject.setGateInput1Name(SelectedChar);
        createNode(OB);
    }
    else
    {
        GateObject.setGateInput1Name(SelectedChar);
    }

    SelectedChar=Line[Simulator::TypeNum+3];

    if((NOT_State==0)&&(Simulator::FindNode(SelectedChar)== -1))
    {
        Node OB(LOW,SelectedChar);
        GateObject.setGateInput2Name(SelectedChar);
        createNode(OB);
    }
    else if(NOT_State==0)
    {
        GateObject.setGateInput2Name(SelectedChar);
    }
    if(NOT_State==0)
    {
        SelectedChar = Line[Simulator::TypeNum + 5];
    }
    if(Simulator::FindNode(SelectedChar)== -1)
    {
        Node OB(LOW,SelectedChar);
        GateObject.setGateOutputName(SelectedChar);
        createNode(OB);
    }
    else
    {
        GateObject.setGateOutputName(SelectedChar);
    }

    Simulator::postGate(GateObject);
}