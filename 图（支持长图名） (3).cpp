
#include <iostream>
#include<iomanip>
#include<queue>
#include<string>
using namespace std;
 
const int DefaultVertices = 30; // Ĭ����󶥵���
const int maxWeight = 100000; // ����������ֵ��=��
template <class T, class E>
class GraphMatrix {
public:
  
    GraphMatrix(int sz=DefaultVertices); // ���캯��
    ~GraphMatrix(); // ��������
    void inputGraph(); // ���������ڽӾ����ͼ
    void outputGraph(); // ���ͼ�����ж���ͱ���Ϣ
    T getValue(int i); // ȡ����i��ֵ��i��������0
    E getWeight(int v1, int v2); // ȡ��(v1, v2)�ϵ�Ȩֵ
    int getFirstNeighbor(int v); // ȡ����v�ĵ�һ���ڽӶ���
    int getNextNeighbor(int v, int w); // ȡv���ڽӶ���w����һ���ڽӶ���
    bool insertVertex(const T& vertex); // ���붥��vertice
    bool insertEdge(int v1, int v2, E cost); // �����(v1, v2)ȨֵΪcost
    bool removeVertex(int v); // ɾȥ����v����������������ı�
    bool removeEdge(int v1, int v2); // ��ͼ��ɾȥ��(v1, v2)
    int getVertexPos(T vertex); // ��������vertice��ͼ�е�λ��
    void display( ); 
    void DFS(int v);
    void reset(){int i;for(i=0;i<numVertices;i++)visited[i]=false;}
	void BFS(int v );
private:
    int maxVertices; // ͼ�����Ķ�����
    int numEdges; // ��ǰ����
    int numVertices; // ��ǰ������
    T *VerticesList; // �����
    bool * visited;
    E **Edge; // �ڽӾ���
};
template <class T, class E>
void GraphMatrix<T, E>::DFS(int v){ //�����ڽӾ����������ȱ���
	cout << VerticesList[v]<< "\t";
	visited[v] = true;
	for(int i = 0 ; i < numVertices ; i++)
	{ //���μ��v �������ڽӵ�
		if(Edge[v][i] ==1&& !visited[i]){ //v��w �ڽӲ���w δ������
			DFS(i ); //�ӽڵ�w �������ݹ�������ȱ���
		}
	}
	 
}
 
 template <class T, class E>
void GraphMatrix<T, E>::display()
{
	int i,j;
	cout<<"�ڽӾ�����:\n";
	for(i=0;i<numVertices;i++)
	 {
	 
	  for(j=0;j<numVertices;j++)
	    cout<<setw(8)<<Edge[i][j];
	 cout<<endl;
     }
}
template <class T, class E>
void GraphMatrix<T, E>::BFS(int v ){
	int u,w;
	cout <<VerticesList[v]<< "\t";	//����ĳ��������һά�����е��±�
	visited[v]=true;	//���ʵ�v�����㣬���÷��ʱ�־������ӦֵΪtrue
	queue<int> q;	//��ʼ������
    q.push(v);
	while(!q.empty()){	//���зǿ�
		u=q.front();q.pop();	//��ͷ������Ӳ�������Ϊu
		// ȡ����v�ĵ�һ���ڽӶ���
        
         
		for( w=getFirstNeighbor(u); w!=-1; w=getNextNeighbor(u,w))//���μ��u�������ڽӵ�w
		{
		
	        if(!visited[w]){	//wΪu����δ���ʵ��ڽӶ���
				cout <<VerticesList[w]<< "\t";	//����ѷ��ʹ��Ķ����±�
				visited[w]=true;	//�����ʹ��Ķ�����Ϊtrue
				q.push(w);	//�±�Ϊw�Ķ������
			}
		}
			//getFirstNeighbor��ʾu�ĵ�һ���ڽӵ�
		//w>=0��ʾ�����ڽӵ�
		//getNextNeighbor��ʾu�������w����һ���ڽӵ�	
				
		
	}
}
template <class T, class E>
GraphMatrix<T, E>::GraphMatrix(int sz) {
    int i, j;
    
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    VerticesList = new T[maxVertices]; // �������������
    Edge = new E*[maxVertices]; // �����ڽӾ�������
    for(i = 0; i < maxVertices; i++)
        Edge[i] = new E[maxVertices];
    for(i = 0; i < maxVertices; i++) { // �ڽӾ����ʼ��
        for(j = 0; j < maxVertices; j++)
        {
            if(i == j) // ����ԽǴ�����Ϊͬһ����
                Edge[i][j] = 0;
            else // ����ͬһ����ģ���������һ��ʼû�б�������Ϊ������
                Edge[i][j] = maxWeight;
        }
    }
}
 
// ��������
template <class T, class E>
GraphMatrix<T, E>::~GraphMatrix() {
    delete []VerticesList; // �ͷŶ�̬����Ŀռ�
    delete []Edge;
}
 
// ���������ڽӾ����ͼ
template <class T, class E>
void GraphMatrix<T, E>::inputGraph() {
    int i, j, k;
    int n, m; // Ҫ����Ķ������ͱ���
    T e1, e2; // �ߵ����˶���
    E weight; // �߶�Ӧ��Ȩֵ
    
    cout << "�����붥�����ͱ���:" << endl;
    cin >> n >> m;
    visited=new bool[n];
    cout << "�����붥�㣺" << endl;
    for(i = 0; i < n; i++) { // �������������
        cin >> e1;
        insertVertex(e1); // ����
        visited[i]=false;
    }
    cout << "������ߵ����˶����Ȩֵ:" << endl;
    i = 0;
    while(i < m){ // �����
        cin >> e1 >> e2 >> weight; // ����˵���Ϣ
        j = getVertexPos(e1); // �鶥���
        k = getVertexPos(e2);
        if(j == -1 || k == -1)
            cout << "�����˵���Ϣ������������!" << endl;
        else {
            insertEdge(j, k, weight);
            i++;
        }
    } // for����
}
 
// ���ͼ�����ж���ͱ���Ϣ
template <class T, class E>
void GraphMatrix<T, E>::outputGraph() {
    int i, j, n, m;
    T e1, e2;
    E w;
    
    n = numVertices;
    m = numEdges;
    cout << "������Ϊ��" << n << "������Ϊ��" << m << endl;
    for(i = 0; i < n; i++) {
        for(j = i+1; j < n; j++) {
            w = getWeight(i, j); // ȡ����Ȩֵ
            if(w > 0 && w < maxWeight) { // ��Ч��������������ڱ�
                e1 = getValue(i);
                e2 = getValue(j);
                cout << "(" << e1 << "," << e2 << "," << w << ")" << endl;
            }
        }
    } // for
}
 
// ��������vertice��ͼ�е�λ��
template <class T, class E>
int GraphMatrix<T, E>::getVertexPos(T vertex) {
    for(int i = 0; i < numVertices; i++)
        if(VerticesList[i] == vertex)
            return i;
    return -1;
}
 
// ȡ����i��ֵ��i��������NULL
template <class T, class E>
T GraphMatrix<T, E>::getValue(int i) {
    if(i >= 0 && i < numVertices)
        return VerticesList[i];
   // return 0;
}
 
// ȡ��(v1, v2)�ϵ�Ȩֵ
template <class T, class E>
E GraphMatrix<T, E>::getWeight(int v1, int v2) {
    if(v1 != -1 && v2 != -1) // ��������������
        return Edge[v1][v2];
    return 0;
}
 
// ȡ����v�ĵ�һ���ڽӶ���
template <class T, class E>
int GraphMatrix<T, E>::getFirstNeighbor(int v) {
    if(v != -1) {
        for(int col = 0; col < numVertices; col++)
            if(Edge[v][col] > 0 && Edge[v][col] <maxWeight)
                return col;
    }
    return -1;
}
 
// ȡv���ڽӶ���w����һ���ڽӶ���
template <class T, class E>
int GraphMatrix<T, E>::getNextNeighbor(int v, int w) {
    if(v != -1 && w != -1) {
        for(int col = w+1; col < numVertices; col++) {
            if(Edge[v][col] > 0 && Edge[v][col] < maxWeight)
                return col;
        }
    }
    return -1;
}
 
// ���붥��vertice
template <class T, class E>
bool GraphMatrix<T, E>::insertVertex(const T& vertex) {
    if(numVertices == maxVertices) // �������
        return false;
    VerticesList[numVertices++] = vertex;
    return true;
}
 
// �����(v1, v2)ȨֵΪcost
template <class T, class E>
bool GraphMatrix<T, E>::insertEdge(int v1, int v2, E cost) 
{
    if(v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices && Edge[v1][v2] == maxWeight) { // ����v1,v2�����ڣ�����v1��v2û�б�
        Edge[v1][v2] = cost;//Edge[v2][v1] = cost;
        numEdges++;
        return true;
    }
    return false;
}
 
// ɾȥ����v����������������ı�
template <class T, class E>
bool GraphMatrix<T, E>::removeVertex(int v) {
    if(v < 0 && v > numVertices) // v����ͼ�У���ɾ��
        return false;
    if(numVertices == 1) // ֻʣһ�����㣬��ɾ��
        return false;
    int i, j;
    
    VerticesList[v] = VerticesList[numVertices-1]; // �����һ�����������ǰҪɾ�Ķ���
    // ɾ����v���������
    for(i = 0; i < numVertices; i++) {
        if(Edge[i][v] > 0 && Edge[i][v] < maxWeight)
            numEdges--;
    }
    // �����һ�У����v��
    for(i = 0; i < numVertices; i++)
        Edge[i][v] = Edge[i][numVertices-1];
    numVertices--; // ��������1
    // �����һ�У����v��
    for(j = 0; j < numVertices; j++)
        Edge[v][j] = Edge[numVertices][j];
    return true;
}
 
// ��ͼ��ɾȥ��(v1, v2)
template <class T, class E>
bool  GraphMatrix<T, E>::removeEdge(int v1, int v2) {
    if(v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices && Edge[v1][v2] < maxWeight) {
        Edge[v1][v2] = Edge[v2][v1] = maxWeight;
        numEdges--; // ������1
        return true;
    }
    return false;
}

 
int main( ) {
    GraphMatrix<string, int> st; // ��������
    bool finished = false;
    int choice;
    string e1, e2, next;
    int weight;
    
    while(!finished) {
        cout << "[1]���������ڽӾ����ͼ" << endl;
        cout << "[2]���ͼ�����ж���ͱ���Ϣ" << endl;
        cout << "[3]ȡ����v�ĵ�һ���ڽӶ���" << endl;
        cout << "[4]ȡv���ڽӶ���w����һ���ڽӶ���" << endl;
        cout << "[5]���붥��" << endl;
        cout << "[6]�����" << endl;
        cout << "[7]ɾ������" << endl;
        cout << "[8]ɾ����" << endl;
        cout<<  "[9]����������� "<<endl;
        cout<<  "[10]����������� "<<endl;
        cout << "[11]�˳�" << endl;
        cout << "������ѡ��[1-11]��";
        cin >> choice;
        switch(choice) {
            case 1:
                st.inputGraph();
                st.display();
                break;
            case 2:
                st.outputGraph();
                break;
            case 3:
                cout << "�����붥��:";
                cin >> e1;
                e2 = st.getValue(st.getFirstNeighbor(st.getVertexPos(e1)));
                if(e2.length()>0)
                    cout << "����" << e1 << "�ĵ�һ���ڽӶ���Ϊ:" << e2 << endl;
                else
                    cout << "����" << e1 << "û���ڽӶ��㣡" << endl;
                break;
            case 4:
                cout << "�����붥��v���ڽӶ���w:";
                cin >> e1 >> e2;
                next = st.getValue(st.getNextNeighbor(st.getVertexPos(e1), st.getVertexPos(e2)));
                if(next.length()>0)
                    cout << "����" << e1 << "���ڽӶ���" << e2 << "����һ���ڽӶ���Ϊ:" << next << endl;
                else
                    cout << "����" << e1 << "���ڽӶ���" << e2 << "û����һ���ڽӶ��㣡" << endl;
                break;
            case 5:
                cout << "������Ҫ����Ķ��㣺";
                cin >> e1;
                if(st.insertVertex(e1))
                    cout << "����ɹ���" << endl;
                else
                    cout << "������������ʧ�ܣ�" << endl;
                break;
            case 6:
                cout << "������Ҫ����ıߵ���Ϣ:" << endl;
                cin >> e1 >> e2 >> weight;
                st.insertEdge(st.getVertexPos(e1), st.getVertexPos(e2), weight);
                break;
            case 7:
                cout << "������Ҫɾ���Ķ��㣺";
                cin >> e1;
                if(st.removeVertex(st.getVertexPos(e1)))
                    cout << "����" << e1 << "��ɾ��!" << endl;
                else
                    cout << "����" << e1 << "����ͼ��!"  << endl;
                break;
            case 8:
                cout << "������Ҫɾ���ıߵ������˵㣺" << endl;
                cin >> e1 >> e2;
                st.removeEdge(st.getVertexPos(e1), st.getVertexPos(e2));
                break;
            case 9:
            	 st.reset();
				 st.DFS(0);
				 cout<<endl;
				 break;
			case 10:
				st.reset();
				 st.BFS(0);
				 cout<<endl;
				 break;
				break;
            case 11:
                finished = true;
                break;
            default:
                cout << "ѡ�������������������!" << endl;
        }
    }
    return 0;
}
