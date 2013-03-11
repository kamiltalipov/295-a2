
struct Edge {
	int EndVertex;
	int Cost;
};

struct BestPathTreeNode {
	int Vertex;
	int Length;
	int PrevVertex;

	BestPathTreeNode() : Vertex( -1 ), Length( -1 ), PrevVertex( -1 ) {}
};

class FrontVerticies {
public:
	FrontVerticies( vector<BestPathTreeNode>& bestPathTree )
	bool Has( int vertex ) const;
	int GetLength( int vertex ) const;
	void AddNewVertex( int vertex, int newLength, int prevVertex );
	void DecreaseKey( int vertex, int newLength, int prevVertex );
	
	int Size() const;
	const BestPathTreeNode& ExtractMin();

private:
	vector<BestPathTreeNode>& bestPathTree;
};

bool FrontVerticies::Has( int vertex ) const
{
	return bestPathTree[vertex].Length != -1;
}

int FrontVerticies::GetLength( int vertex ) const
{
	assert( !Has( vertex ) );
	return bestPathTree[vertex].Length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Dijkstra( const vector<vector<Edge>>& graph, int startVertex, vector<BestPathTreeNode>& bestPathTree )
{
	bestPathTree.resize( graph.size() );
	for( int i = 0; i < bestPathTree.size(); i++ ) {
		bestPathTree[i].Vertex = i;
	}

	FrontVerticies queue( bestPathTree );
	queue.AddNewVertex( startVertex, 0, -1 );
	while( queue.Size() > 0 ) {
		const BestPathTreeNode& node = queue.ExtractMin();
		for( int i = 0; i < graph[node.Vertex].size(); i++ ) {
			int toVertex = graph[node.Vertex][i].EndVertex;
			if( !queue.Has( toVertex ) ) {
				queue.AddNewVertex( toVertex, node.Length + graph[node.Vertex][i].Cost );
			} else {
				int estimatedCost = node.Length + graph[node.Vertex][i].Cost;
				if( queue.GetLength( toVertex ) > estimatedCost ) {
					queue.DecreaseKey( toVertex, estimatedCost, node.Vertex );
				}
			}
		}
	}
}