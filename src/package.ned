package project;

@license(LGPL);

network Network
{
    parameters:
        int WS = default(5);
        double TO = default(10.0);
        double PT = default(0.5);
        double TD = default(1.0);
        double ED = default(4.0);
        double DD = default(0.1);
        double LP = default(0.1);
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

