#include "graph.h"
#include <iostream>
#include <gtest/gtest.h>
namespace {
    class GraphIntTest : public ::testing::Test {
    protected:
        Graph<int, int, int> graph;
        GraphIntTest() {}
        virtual ~GraphIntTest() {}
        virtual void SetUp() {}
        virtual void TearDown() {}
    };
TEST_F(GraphIntTest, GraphInsertNodeTest){
    graph.insertNode(1, 10);
    graph.insertNode(2, 20);
    graph.insertNode(3, 5);
    graph.insertNode(4, -10);
    EXPECT_EQ(graph[1], 10);
    EXPECT_EQ(graph[2], 20);
    EXPECT_EQ(graph[3], 5);
    EXPECT_EQ(graph[4], -10);

    graph[1] = -5;
    EXPECT_EQ(graph[1], -5);

    auto it = graph.insertNode(5, 123);
    EXPECT_EQ(it->second->getId(), 5);
    EXPECT_EQ(it->second->getValue(), 123);

    ASSERT_THROW(graph[6] = -5, logic_error);
    ASSERT_THROW(graph.insertNode(4, 5), logic_error);
}
TEST_F(GraphIntTest, GraphInsertEdgeTest){
    graph.insertNode(1, 10);
    graph.insertNode(2, 20);
    graph.insertNode(3, 5);
    graph.insertNode(4, -10);
    graph.insertEdge(1, 2, 70);
    graph.insertEdge(2, 1, 7);
    graph.insertEdge(2, 3, 10);
    graph.insertEdge(2, 4, 10000);
    EXPECT_EQ(graph.getOutEdges(1)[0].second, 70);
    EXPECT_EQ(graph.getInEdges(1)[0].second, 7);
    EXPECT_TRUE(graph.getOutEdges(2)[0].second==10 || graph.getOutEdges(2)[0].second==10000);

    graph.insertNode(5, 90);
    auto it = graph.insertEdge(1, 5, 123);
    EXPECT_EQ(it->second->getValue(), 123);
    EXPECT_EQ(it->second->getNodes(), make_pair(1, 5));
    EXPECT_EQ(make_pair(reinterpret_cast<int*>(it->second->getNodesPointers().first.lock().get())+1,
                        reinterpret_cast<int*>(it->second->getNodesPointers().second.lock().get())+1),
              make_pair(&graph[it->first.first],&graph[it->first.second]));

    ASSERT_THROW(graph.insertEdge(1, 2, 80), logic_error);
    ASSERT_THROW(graph.insertEdge(5, 6, 100), logic_error);
    ASSERT_THROW(graph.insertEdge(6, 5, 120), logic_error);
}
TEST_F(GraphIntTest, GraphEraseEdgeTest){
    graph.insertNode(1, 5);
    graph.insertNode(2, -10);
    graph.insertEdge(1, 2, 20);
    graph.eraseEdge(1, 2);
    EXPECT_TRUE(graph.getOutEdges(1).empty());

    graph.insertNode(3, 90);
    graph.insertNode(4, -50);
    graph.insertNode(5, 120);
    graph.insertEdge(1, 3, 20);
    graph.insertEdge(1, 4, 30);
    graph.insertEdge(1, 5, 40);
    graph.eraseEdge(1, 3);
    graph.eraseEdge(1, 4);
    EXPECT_EQ(graph.getOutEdges(1)[0].second, 40);
    graph.eraseEdge(1, 5);
    EXPECT_TRUE(graph.getOutEdges(1).empty());

    auto it = graph.insertEdge(1, 3, 50);
    EXPECT_EQ(graph.getOutEdges(1)[0].second, 50);
    graph.eraseEdge(it);
    EXPECT_TRUE(graph.getOutEdges(1).empty());

    ASSERT_THROW(graph.eraseEdge(77, 88), logic_error);

    it = graph.insertEdge(1, 2, 400);
    graph.eraseEdge(1, 2);
    //ASSERT_DEATH(graph.eraseEdge(it), "");
}
TEST_F(GraphIntTest, GraphEraseNodeTest){
    graph.insertNode(1, 30000000);
    auto it = graph.insertNode(2, -30000000);
    graph.insertNode(3, -10000000);
    graph.insertNode(4, 10000000);

    graph.insertEdge(2, 3, 1000);
    graph.insertEdge(2, 4, 2000);
    graph.insertEdge(2, 1, 4000);
    graph.insertEdge(4, 1, 4000);
    EXPECT_EQ(graph.getOutEdges(2).size(), 3);
    EXPECT_EQ(graph.getInEdges(1).size(), 2);
    graph.eraseNode(4);
    EXPECT_EQ(graph.getOutEdges(2).size(), 2);
    EXPECT_EQ(graph.getInEdges(1).size(), 1);

    graph.eraseNode(it);
    EXPECT_TRUE(graph.getOutEdges(1).empty());
    EXPECT_TRUE(graph.getInEdges(1).empty());
    EXPECT_TRUE(graph.getOutEdges(3).empty());
    EXPECT_TRUE(graph.getInEdges(3).empty());
    graph.eraseNode(1);
    graph.eraseNode(3);
    ASSERT_THROW(graph.eraseNode(2), logic_error);
}
TEST_F(GraphIntTest, GraphGetsTest){
    graph.insertNode(1, 30000000);
    EXPECT_EQ(graph.getAllNodes().size(), 1);
    graph.insertNode(2, -30000000);
    EXPECT_EQ(graph.getAllNodes().size(), 2);
    graph.insertNode(3, -10000000);
    EXPECT_EQ(graph.getAllNodes().size(), 3);
    graph.insertNode(4, 10000000);
    EXPECT_EQ(graph.getAllNodes().size(), 4);

    graph.insertEdge(2, 3, 1000);
    graph.insertEdge(2, 4, 2000);
    EXPECT_EQ(graph.getOutNodes(2).size(), 2);
    EXPECT_EQ(graph.getOutEdges(2).size(), 2);
    EXPECT_EQ(graph.getOutNodes(4).size(), 0);
    EXPECT_EQ(graph.getOutEdges(4).size(), 0);
    EXPECT_EQ(graph.getInNodes(4)[0].first, 2);
    EXPECT_EQ(graph.getInNodes(4)[0].second, -30000000);
    EXPECT_EQ(graph.getInEdges(4)[0].first, 2);
    EXPECT_EQ(graph.getInEdges(4)[0].second, 2000);
    EXPECT_EQ(graph.getInNodes(2).size(), 0);
    EXPECT_EQ(graph.getInEdges(2).size(), 0);

    ASSERT_THROW(graph.getInEdges(5), logic_error);
    ASSERT_THROW(graph.getInNodes(6), logic_error);
    ASSERT_THROW(graph.getOutEdges(7), logic_error);
    ASSERT_THROW(graph.getOutNodes(8), logic_error);
}

TEST_F(GraphIntTest, GraphDfsIteratorTest){
    graph.insertNode(1, 30000000);
    graph.insertNode(2, -30000000);
    graph.insertNode(3, -10000000);
    graph.insertNode(4, 10000000);
    graph.insertNode(5, 2);
    graph.insertNode(6, 2);

    graph.insertEdge(1, 2, 3000);
    graph.insertEdge(2, 3, 1000);
    graph.insertEdge(2, 4, 2000);
    graph.insertEdge(2, 1, 4000);
    graph.insertEdge(4, 1, 4000);

    auto it = graph.begin_dfs(1);
    EXPECT_EQ(it->getId(), 1);
    EXPECT_EQ((++it)->getId(), 2);
    EXPECT_TRUE((++it)->getId()==3 || (it)->getId()==4);
    EXPECT_TRUE((++it)->getId()==3 || (it)->getId()==4);
    EXPECT_EQ((++it)->getId(), 5);
    EXPECT_EQ((++it)->getId(), 6);
    ASSERT_THROW((++it)->getId(), logic_error);
    ASSERT_NO_THROW(++it);

    it = graph.begin_dfs(6);
    EXPECT_EQ(it->getId(), 6);
    EXPECT_EQ((++it)->getId(), 1);
    EXPECT_EQ((++it)->getId(), 2);
    EXPECT_TRUE((++it)->getId()==3 || (it)->getId()==4);
    EXPECT_TRUE((++it)->getId()==3 || (it)->getId()==4);
    EXPECT_EQ((++it)->getId(), 5);
    ASSERT_THROW((++it)->getId(), logic_error);
    ASSERT_NO_THROW(++it);

    it = graph.begin_dfs(4);
    EXPECT_EQ(it->getId(), 4);
    EXPECT_EQ((++it)->getId(), 1);
    EXPECT_EQ((++it)->getId(), 2);
    auto temp1 = it;
    EXPECT_EQ((++it)->getId(), 3);
    EXPECT_EQ((++it)->getId(), 5);
    EXPECT_EQ((++it)->getId(), 6);
    ASSERT_THROW((++it)->getId(), logic_error);
    ASSERT_NO_THROW(++it);

    it = graph.begin_dfs(3);
    EXPECT_EQ(it->getId(), 3);
    EXPECT_EQ((++it)->getId(), 1);
    EXPECT_EQ((++it)->getId(), 2);
    auto temp2 = it;
    EXPECT_EQ((++it)->getId(), 4);
    EXPECT_EQ((++it)->getId(), 5);
    EXPECT_EQ((++it)->getId(), 6);
    ASSERT_THROW((++it)->getId(), logic_error);
    ASSERT_NO_THROW(++it);

    it = graph.begin_dfs(3);
    EXPECT_EQ((*(it++)).getId(), 3);
    EXPECT_EQ((it++)->getId(), 1);
    EXPECT_TRUE(temp2==it);
    EXPECT_TRUE(temp1!=it);

    temp1.swap(temp2);
    EXPECT_TRUE(temp1==it);
    EXPECT_TRUE(temp2!=it);

    for (auto iter = graph.begin_dfs(); iter!=graph.end_dfs(); iter++)
        iter->getId();
}

TEST_F(GraphIntTest, GraphBfsIteratorTest){
    graph.insertNode(1, 30000000);
    graph.insertNode(2, -30000000);
    graph.insertNode(3, -10000000);
    graph.insertNode(4, 10000000);
    graph.insertNode(5, 2);
    graph.insertNode(6, 20);
    graph.insertNode(7, 200);
    graph.insertNode(8, 300);

    graph.insertEdge(1, 2, 3000);
    graph.insertEdge(2, 3, 1000);
    graph.insertEdge(2, 4, 2000);
    graph.insertEdge(2, 6, 300);
    graph.insertEdge(2, 1, 4000);
    graph.insertEdge(4, 5, 500);
    graph.insertEdge(3, 7, 200);
    graph.insertEdge(6, 8, 800);

    auto it = graph.begin_bfs(1);
    EXPECT_EQ(it->getId(), 1);
    EXPECT_EQ((++it)->getId(), 2);
    EXPECT_TRUE((++it)->getId()==6 || (it)->getId()==4 || (it)->getId()==3);
    EXPECT_TRUE((++it)->getId()==6 || (it)->getId()==4 || (it)->getId()==3);
    EXPECT_TRUE((++it)->getId()==6 || (it)->getId()==4 || (it)->getId()==3);
    EXPECT_TRUE((++it)->getId()==5 || (it)->getId()==8 || (it)->getId()==7);
    EXPECT_TRUE((++it)->getId()==5 || (it)->getId()==8 || (it)->getId()==7);
    EXPECT_TRUE((++it)->getId()==5 || (it)->getId()==8 || (it)->getId()==7);
    ASSERT_THROW((++it)->getId(), logic_error);
    ASSERT_NO_THROW(++it);
}
}
int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
