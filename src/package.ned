package project;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    submodules:
        coordinator: Coordinator {
            @display("p=141,158");
        }
        Node0: Node {
            @display("p=36,56");
            Index = "0";
        }
        Node1: Node {
            @display("p=237,56");
            Index = "1";
        }
    connections:
        coordinator.out1 --> Node1.inCoord;
        coordinator.out0 --> Node0.inCoord;
        Node0.outNode --> Node1.inNode;
        Node1.outNode --> Node0.inNode;
}

