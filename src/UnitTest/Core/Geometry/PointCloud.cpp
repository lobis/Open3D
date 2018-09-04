// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include "UnitTest.h"
#include "Core/Geometry/PointCloud.h"

#include <algorithm>
using namespace std;

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, Constructor)
{
    open3d::PointCloud pc;

    // inherited from Geometry2D
    EXPECT_EQ(open3d::Geometry::GeometryType::PointCloud, pc.GetGeometryType());
    EXPECT_EQ(3, pc.Dimension());

    // public member variables
    EXPECT_EQ(0, pc.points_.size());
    EXPECT_EQ(0, pc.normals_.size());
    EXPECT_EQ(0, pc.colors_.size());

    // public members
    EXPECT_TRUE(pc.IsEmpty());
    EXPECT_EQ(Eigen::Vector3d(0, 0, 0), pc.GetMinBound());
    EXPECT_EQ(Eigen::Vector3d(0, 0, 0), pc.GetMaxBound());
    EXPECT_FALSE(pc.HasPoints());
    EXPECT_FALSE(pc.HasNormals());
    EXPECT_FALSE(pc.HasColors());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_MemberData)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, Clear)
{
    Eigen::Vector3d p0 = { 150, 230, 400 };
    Eigen::Vector3d p1 = { 250, 230, 400 };
    Eigen::Vector3d p2 = { 150, 130, 400 };
    Eigen::Vector3d p3 = { 150, 230, 300 };

    open3d::PointCloud pc;

    pc.points_.push_back(p0);
    pc.points_.push_back(p1);
    pc.points_.push_back(p2);
    pc.points_.push_back(p3);

    EXPECT_TRUE(pc.HasPoints());

    pc.Clear();

    // public members
    EXPECT_TRUE(pc.IsEmpty());
    EXPECT_EQ(Eigen::Vector3d(0, 0, 0), pc.GetMinBound());
    EXPECT_EQ(Eigen::Vector3d(0, 0, 0), pc.GetMaxBound());
    EXPECT_FALSE(pc.HasPoints());
    EXPECT_FALSE(pc.HasNormals());
    EXPECT_FALSE(pc.HasColors());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, IsEmpty)
{
    Eigen::Vector3d p0 = { 150, 230, 400 };
    Eigen::Vector3d p1 = { 250, 230, 400 };
    Eigen::Vector3d p2 = { 150, 130, 400 };
    Eigen::Vector3d p3 = { 150, 230, 300 };

    open3d::PointCloud pc;

    pc.points_.push_back(p0);
    pc.points_.push_back(p1);
    pc.points_.push_back(p2);
    pc.points_.push_back(p3);

    EXPECT_FALSE(pc.IsEmpty());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, GetMinBound)
{
    Eigen::Vector3d p0 = { 150, 230, 400 };
    Eigen::Vector3d p1 = { 250, 230, 400 };
    Eigen::Vector3d p2 = { 150, 130, 400 };
    Eigen::Vector3d p3 = { 150, 230, 300 };

    open3d::PointCloud pc;

    pc.points_.push_back(p0);
    pc.points_.push_back(p1);
    pc.points_.push_back(p2);
    pc.points_.push_back(p3);

    EXPECT_EQ(Eigen::Vector3d(150, 130, 300), pc.GetMinBound());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, GetMaxBound)
{
    Eigen::Vector3d p0 = { 150, 230, 400 };
    Eigen::Vector3d p1 = { 250, 230, 400 };
    Eigen::Vector3d p2 = { 150, 130, 400 };
    Eigen::Vector3d p3 = { 150, 230, 300 };

    open3d::PointCloud pc;

    pc.points_.push_back(p0);
    pc.points_.push_back(p1);
    pc.points_.push_back(p2);
    pc.points_.push_back(p3);

    EXPECT_EQ(Eigen::Vector3d(250, 230, 400), pc.GetMaxBound());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, Transform)
{
    Eigen::Vector3d p0 = { 150, 230, 400 };
    Eigen::Vector3d p1 = { 250, 230, 400 };
    Eigen::Vector3d p2 = { 150, 130, 400 };
    Eigen::Vector3d p3 = { 150, 230, 300 };

    Eigen::Vector3d n0 = { 0.150, 0.230, 0.400 };
    Eigen::Vector3d n1 = { 0.250, 0.230, 0.400 };
    Eigen::Vector3d n2 = { 0.150, 0.130, 0.400 };
    Eigen::Vector3d n3 = { 0.150, 0.230, 0.300 };

    open3d::PointCloud pc;

    pc.points_.push_back(p0);
    pc.points_.push_back(p1);
    pc.points_.push_back(p2);
    pc.points_.push_back(p3);

    pc.normals_.push_back(n0);
    pc.normals_.push_back(n1);
    pc.normals_.push_back(n2);
    pc.normals_.push_back(n3);

    Eigen::Matrix4d transformation;
    transformation << 0.10, 0.20, 0.30, 0.40,
                      0.50, 0.60, 0.70, 0.80,
                      0.90, 0.10, 0.11, 0.12,
                      0.13, 0.14, 0.15, 0.16;

    pc.Transform(transformation);

    EXPECT_DOUBLE_EQ(181.40, (pc.points_[0][0, 0]));
    EXPECT_DOUBLE_EQ(493.80, (pc.points_[0][0, 1]));
    EXPECT_DOUBLE_EQ(202.12, (pc.points_[0][0, 2]));
    EXPECT_DOUBLE_EQ(191.40, (pc.points_[1][0, 0]));
    EXPECT_DOUBLE_EQ(543.80, (pc.points_[1][0, 1]));
    EXPECT_DOUBLE_EQ(292.12, (pc.points_[1][0, 2]));
    EXPECT_DOUBLE_EQ(161.40, (pc.points_[2][0, 0]));
    EXPECT_DOUBLE_EQ(433.80, (pc.points_[2][0, 1]));
    EXPECT_DOUBLE_EQ(192.12, (pc.points_[2][0, 2]));
    EXPECT_DOUBLE_EQ(151.40, (pc.points_[3][0, 0]));
    EXPECT_DOUBLE_EQ(423.80, (pc.points_[3][0, 1]));
    EXPECT_DOUBLE_EQ(191.12, (pc.points_[3][0, 2]));

    EXPECT_DOUBLE_EQ(0.181, (pc.normals_[0][0, 0]));
    EXPECT_DOUBLE_EQ(0.493, (pc.normals_[0][0, 1]));
    EXPECT_DOUBLE_EQ(0.202, (pc.normals_[0][0, 2]));
    EXPECT_DOUBLE_EQ(0.191, (pc.normals_[1][0, 0]));
    EXPECT_DOUBLE_EQ(0.543, (pc.normals_[1][0, 1]));
    EXPECT_DOUBLE_EQ(0.292, (pc.normals_[1][0, 2]));
    EXPECT_DOUBLE_EQ(0.161, (pc.normals_[2][0, 0]));
    EXPECT_DOUBLE_EQ(0.433, (pc.normals_[2][0, 1]));
    EXPECT_DOUBLE_EQ(0.192, (pc.normals_[2][0, 2]));
    EXPECT_DOUBLE_EQ(0.151, (pc.normals_[3][0, 0]));
    EXPECT_DOUBLE_EQ(0.423, (pc.normals_[3][0, 1]));
    EXPECT_DOUBLE_EQ(0.191, (pc.normals_[3][0, 2]));
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, HasPoints)
{
    Eigen::Vector3d p0 = { 150, 230, 400 };
    Eigen::Vector3d p1 = { 250, 230, 400 };
    Eigen::Vector3d p2 = { 150, 130, 400 };
    Eigen::Vector3d p3 = { 150, 230, 300 };

    open3d::PointCloud pc;

    pc.points_.push_back(p0);
    pc.points_.push_back(p1);
    pc.points_.push_back(p2);
    pc.points_.push_back(p3);

    EXPECT_TRUE(pc.HasPoints());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, HasNormals)
{
    Eigen::Vector3d p0 = { 150, 230, 400 };
    Eigen::Vector3d p1 = { 250, 230, 400 };
    Eigen::Vector3d p2 = { 150, 130, 400 };
    Eigen::Vector3d p3 = { 150, 230, 300 };

    Eigen::Vector3d n0 = { 0.150, 0.230, 0.400 };
    Eigen::Vector3d n1 = { 0.250, 0.230, 0.400 };
    Eigen::Vector3d n2 = { 0.150, 0.130, 0.400 };
    Eigen::Vector3d n3 = { 0.150, 0.230, 0.300 };

    open3d::PointCloud pc;

    pc.points_.push_back(p0);
    pc.points_.push_back(p1);
    pc.points_.push_back(p2);
    pc.points_.push_back(p3);

    pc.normals_.push_back(n0);
    pc.normals_.push_back(n1);
    pc.normals_.push_back(n2);
    pc.normals_.push_back(n3);

    EXPECT_TRUE(pc.HasNormals());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, HasColors)
{
    Eigen::Vector3d p0 = { 150, 230, 400 };
    Eigen::Vector3d p1 = { 250, 230, 400 };
    Eigen::Vector3d p2 = { 150, 130, 400 };
    Eigen::Vector3d p3 = { 150, 230, 300 };

    Eigen::Vector3d c0 = { 150, 230, 200 };
    Eigen::Vector3d c1 = { 250, 230, 200 };
    Eigen::Vector3d c2 = { 150, 130, 200 };
    Eigen::Vector3d c3 = { 150, 230, 100 };

    open3d::PointCloud pc;

    pc.points_.push_back(p0);
    pc.points_.push_back(p1);
    pc.points_.push_back(p2);
    pc.points_.push_back(p3);

    pc.colors_.push_back(c0);
    pc.colors_.push_back(c1);
    pc.colors_.push_back(c2);
    pc.colors_.push_back(c3);

    EXPECT_TRUE(pc.HasColors());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, NormalizeNormals)
{
    Eigen::Vector3d n0 = { 0.150, 0.230, 0.400 };
    Eigen::Vector3d n1 = { 0.250, 0.230, 0.400 };
    Eigen::Vector3d n2 = { 0.150, 0.130, 0.400 };
    Eigen::Vector3d n3 = { 0.150, 0.230, 0.300 };

    open3d::PointCloud pc;

    pc.normals_.push_back(n0);
    pc.normals_.push_back(n1);
    pc.normals_.push_back(n2);
    pc.normals_.push_back(n3);

    pc.NormalizeNormals();

    EXPECT_DOUBLE_EQ(0.30916336798746480, (pc.normals_[0][0, 0]));
    EXPECT_DOUBLE_EQ(0.47405049758077938, (pc.normals_[0][0, 1]));
    EXPECT_DOUBLE_EQ(0.82443564796657287, (pc.normals_[0][0, 2]));
    EXPECT_DOUBLE_EQ(0.47638495872919123, (pc.normals_[1][0, 0]));
    EXPECT_DOUBLE_EQ(0.43827416203085595, (pc.normals_[1][0, 1]));
    EXPECT_DOUBLE_EQ(0.76221593396670595, (pc.normals_[1][0, 2]));
    EXPECT_DOUBLE_EQ(0.33591444676679194, (pc.normals_[2][0, 0]));
    EXPECT_DOUBLE_EQ(0.29112585386455303, (pc.normals_[2][0, 1]));
    EXPECT_DOUBLE_EQ(0.89577185804477866, (pc.normals_[2][0, 2]));
    EXPECT_DOUBLE_EQ(0.36882767970367752, (pc.normals_[3][0, 0]));
    EXPECT_DOUBLE_EQ(0.56553577554563894, (pc.normals_[3][0, 1]));
    EXPECT_DOUBLE_EQ(0.73765535940735505, (pc.normals_[3][0, 2]));
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, PaintUniformColor)
{
    Eigen::Vector3d p0 = { 150, 230, 400 };
    Eigen::Vector3d p1 = { 250, 230, 400 };
    Eigen::Vector3d p2 = { 150, 130, 400 };
    Eigen::Vector3d p3 = { 150, 230, 300 };

    open3d::PointCloud pc;

    pc.points_.push_back(p0);
    pc.points_.push_back(p1);
    pc.points_.push_back(p2);
    pc.points_.push_back(p3);

    EXPECT_FALSE(pc.HasColors());

    pc.PaintUniformColor(Eigen::Vector3d(233, 171, 53));

    EXPECT_TRUE(pc.HasColors());

    for (size_t i = 0; i < pc.colors_.size(); i++)
    {
        EXPECT_DOUBLE_EQ(233, (pc.colors_[i][0, 0]));
        EXPECT_DOUBLE_EQ(171, (pc.colors_[i][0, 1]));
        EXPECT_DOUBLE_EQ( 53, (pc.colors_[i][0, 2]));
    }
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, OperatorAppend)
{
    Eigen::Vector3d p0 = { 150, 230, 400 };
    Eigen::Vector3d p1 = { 250, 230, 400 };
    Eigen::Vector3d p2 = { 150, 130, 400 };
    Eigen::Vector3d p3 = { 150, 230, 300 };

    Eigen::Vector3d p4 = {  75, 115, 200 };
    Eigen::Vector3d p5 = { 125, 115, 200 };
    Eigen::Vector3d p6 = {  75,  65, 200 };
    Eigen::Vector3d p7 = {  75, 115, 150 };

    vector<Eigen::Vector3d> p;
    p.push_back(p0);
    p.push_back(p1);
    p.push_back(p2);
    p.push_back(p3);
    p.push_back(p4);
    p.push_back(p3);
    p.push_back(p4);
    p.push_back(p5);
    p.push_back(p6);
    p.push_back(p7);

    Eigen::Vector3d n0 = { 0.150, 0.230, 0.400 };
    Eigen::Vector3d n1 = { 0.250, 0.230, 0.400 };
    Eigen::Vector3d n2 = { 0.150, 0.130, 0.400 };
    Eigen::Vector3d n3 = { 0.150, 0.230, 0.300 };

    Eigen::Vector3d n4 = { 0.075, 0.115, 0.200 };
    Eigen::Vector3d n5 = { 0.125, 0.115, 0.200 };
    Eigen::Vector3d n6 = { 0.075, 0.065, 0.200 };
    Eigen::Vector3d n7 = { 0.075, 0.115, 0.150 };

    vector<Eigen::Vector3d> n;
    n.push_back(n0);
    n.push_back(n1);
    n.push_back(n2);
    n.push_back(n3);
    n.push_back(n4);
    n.push_back(n3);
    n.push_back(n4);
    n.push_back(n5);
    n.push_back(n6);
    n.push_back(n7);

    open3d::PointCloud pc0;
    open3d::PointCloud pc1;

    pc0.points_.push_back(p0);
    pc0.points_.push_back(p1);
    pc0.points_.push_back(p2);
    pc0.points_.push_back(p3);
    pc0.points_.push_back(p4);

    pc1.points_.push_back(p3);
    pc1.points_.push_back(p4);
    pc1.points_.push_back(p5);
    pc1.points_.push_back(p6);
    pc1.points_.push_back(p7);

    pc0.normals_.push_back(n0);
    pc0.normals_.push_back(n1);
    pc0.normals_.push_back(n2);
    pc0.normals_.push_back(n3);
    pc0.normals_.push_back(n4);

    pc1.normals_.push_back(n3);
    pc1.normals_.push_back(n4);
    pc1.normals_.push_back(n5);
    pc1.normals_.push_back(n6);
    pc1.normals_.push_back(n7);

    pc0.PaintUniformColor(Eigen::Vector3d(233, 171, 53));
    pc1.PaintUniformColor(Eigen::Vector3d( 53, 233, 171));

    pc0 += pc1;

    EXPECT_EQ(p.size(), pc0.points_.size());
    for (size_t i = 0; i < 10; i++)
        EXPECT_EQ(p[i], pc0.points_[i]);

    EXPECT_EQ(n.size(), pc0.normals_.size());
    for (size_t i = 0; i < 10; i++)
    {
        EXPECT_DOUBLE_EQ((n[i][0, 0]), (pc0.normals_[i][0, 0]));
        EXPECT_DOUBLE_EQ((n[i][0, 1]), (pc0.normals_[i][0, 1]));
        EXPECT_DOUBLE_EQ((n[i][0, 2]), (pc0.normals_[i][0, 2]));
    }

    EXPECT_EQ(p.size(), pc0.colors_.size());
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_DOUBLE_EQ(233, (pc0.colors_[i][0, 0]));
        EXPECT_DOUBLE_EQ(171, (pc0.colors_[i][0, 1]));
        EXPECT_DOUBLE_EQ( 53, (pc0.colors_[i][0, 2]));
    }

    for (size_t i = 5; i < 10; i++)
    {
        EXPECT_DOUBLE_EQ( 53, (pc0.colors_[i][0, 0]));
        EXPECT_DOUBLE_EQ(233, (pc0.colors_[i][0, 1]));
        EXPECT_DOUBLE_EQ(171, (pc0.colors_[i][0, 2]));
    }
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, OperatorADD)
{
    Eigen::Vector3d p0 = { 150, 230, 400 };
    Eigen::Vector3d p1 = { 250, 230, 400 };
    Eigen::Vector3d p2 = { 150, 130, 400 };
    Eigen::Vector3d p3 = { 150, 230, 300 };

    Eigen::Vector3d p4 = {  75, 115, 200 };
    Eigen::Vector3d p5 = { 125, 115, 200 };
    Eigen::Vector3d p6 = {  75,  65, 200 };
    Eigen::Vector3d p7 = {  75, 115, 150 };

    vector<Eigen::Vector3d> p;
    p.push_back(p0);
    p.push_back(p1);
    p.push_back(p2);
    p.push_back(p3);
    p.push_back(p4);
    p.push_back(p3);
    p.push_back(p4);
    p.push_back(p5);
    p.push_back(p6);
    p.push_back(p7);

    Eigen::Vector3d n0 = { 0.150, 0.230, 0.400 };
    Eigen::Vector3d n1 = { 0.250, 0.230, 0.400 };
    Eigen::Vector3d n2 = { 0.150, 0.130, 0.400 };
    Eigen::Vector3d n3 = { 0.150, 0.230, 0.300 };

    Eigen::Vector3d n4 = { 0.075, 0.115, 0.200 };
    Eigen::Vector3d n5 = { 0.125, 0.115, 0.200 };
    Eigen::Vector3d n6 = { 0.075, 0.065, 0.200 };
    Eigen::Vector3d n7 = { 0.075, 0.115, 0.150 };

    vector<Eigen::Vector3d> n;
    n.push_back(n0);
    n.push_back(n1);
    n.push_back(n2);
    n.push_back(n3);
    n.push_back(n4);
    n.push_back(n3);
    n.push_back(n4);
    n.push_back(n5);
    n.push_back(n6);
    n.push_back(n7);

    open3d::PointCloud pc0;
    open3d::PointCloud pc1;

    pc0.points_.push_back(p0);
    pc0.points_.push_back(p1);
    pc0.points_.push_back(p2);
    pc0.points_.push_back(p3);
    pc0.points_.push_back(p4);

    pc1.points_.push_back(p3);
    pc1.points_.push_back(p4);
    pc1.points_.push_back(p5);
    pc1.points_.push_back(p6);
    pc1.points_.push_back(p7);

    pc0.normals_.push_back(n0);
    pc0.normals_.push_back(n1);
    pc0.normals_.push_back(n2);
    pc0.normals_.push_back(n3);
    pc0.normals_.push_back(n4);

    pc1.normals_.push_back(n3);
    pc1.normals_.push_back(n4);
    pc1.normals_.push_back(n5);
    pc1.normals_.push_back(n6);
    pc1.normals_.push_back(n7);

    pc0.PaintUniformColor(Eigen::Vector3d(233, 171, 53));
    pc1.PaintUniformColor(Eigen::Vector3d( 53, 233, 171));

    open3d::PointCloud pc = pc0 + pc1;

    EXPECT_EQ(5, pc0.points_.size());
    EXPECT_EQ(5, pc0.normals_.size());
    EXPECT_EQ(5, pc0.colors_.size());

    EXPECT_EQ(p.size(), pc.points_.size());
    for (size_t i = 0; i < 10; i++)
        EXPECT_EQ(p[i], pc.points_[i]);

    EXPECT_EQ(n.size(), pc.normals_.size());
    for (size_t i = 0; i < 10; i++)
    {
        EXPECT_DOUBLE_EQ((n[i][0, 0]), (pc.normals_[i][0, 0]));
        EXPECT_DOUBLE_EQ((n[i][0, 1]), (pc.normals_[i][0, 1]));
        EXPECT_DOUBLE_EQ((n[i][0, 2]), (pc.normals_[i][0, 2]));
    }

    EXPECT_EQ(p.size(), pc.colors_.size());
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_DOUBLE_EQ(233, (pc.colors_[i][0, 0]));
        EXPECT_DOUBLE_EQ(171, (pc.colors_[i][0, 1]));
        EXPECT_DOUBLE_EQ( 53, (pc.colors_[i][0, 2]));
    }

    for (size_t i = 5; i < 10; i++)
    {
        EXPECT_DOUBLE_EQ( 53, (pc.colors_[i][0, 0]));
        EXPECT_DOUBLE_EQ(233, (pc.colors_[i][0, 1]));
        EXPECT_DOUBLE_EQ(171, (pc.colors_[i][0, 2]));
    }
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_CreatePointCloudFromFile)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_CreatePointCloudFromDepthImage)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_CreatePointCloudFromRGBDImage)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, SelectDownSample)
{
    vector<Eigen::Vector3d> ref =
    {
        { 347.115873, 184.622468, 609.105862 },\
        { 416.501281, 169.607086, 906.803934 },\
        { 434.513296,   3.231460, 344.942955 },\
        { 598.481300, 833.243294, 233.891705 },\
        { 593.211455, 666.556591, 288.777775 },\
        {  20.023049, 457.701737,  63.095838 },\
        { 910.972031, 482.490657, 215.824959 },\
        { 471.483429, 592.539919, 944.318096 },\
        { 165.974166, 440.104528, 880.075236 },\
        { 204.328611, 889.955644, 125.468476 },\
        { 950.104032,  52.529262, 521.563380 },\
        { 530.807988, 757.293832, 304.295150 },\
        { 619.596484, 281.059412, 786.002098 },\
        { 134.902412, 520.210070,  78.232142 },\
        { 436.496997, 958.636962, 918.930388 },\
        { 593.211455, 666.556591, 288.777775 },\
        { 992.228461, 576.971113, 877.613778 },\
        { 229.136980, 700.619965, 316.867137 },\
        { 400.228622, 891.529452, 283.314746 },\
        { 359.095369, 552.485022, 579.429994 },\
        { 798.440033, 911.647358, 197.551369 },\
        { 437.637597, 931.835056, 930.809795 },\
        { 771.357698, 526.744979, 769.913836 },\
        { 675.475980, 482.950280, 481.935823 },\
        { 352.458347, 807.724520, 919.026474 } \
    };

    int size = 100;
    open3d::PointCloud pc;

    Eigen::Vector3d vmin(0.0, 0.0, 0.0);
    Eigen::Vector3d vmax(1000.0, 1000.0, 1000.0);

    pc.points_.resize(size);
    UnitTest::Rand(pc.points_, vmin, vmax);

    vector<size_t> indices(size / 4);
    UnitTest::Rand<size_t>(indices, 0, size);

    // remove duplicates
    std::vector<size_t>::iterator it;
    it = unique(indices.begin(), indices.end());
    indices.resize(distance(indices.begin(), it));

    auto output_pc = open3d::SelectDownSample(pc, indices);

    for (size_t i = 0; i < indices.size(); i++)
    {
        EXPECT_NEAR(ref[i](0, 0), output_pc->points_[i](0, 0), UnitTest::THRESHOLD_DOUBLE);
        EXPECT_NEAR(ref[i](0, 1), output_pc->points_[i](0, 1), UnitTest::THRESHOLD_DOUBLE);
        EXPECT_NEAR(ref[i](0, 2), output_pc->points_[i](0, 2), UnitTest::THRESHOLD_DOUBLE);
    }
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_VoxelDownSample)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_UniformDownSample)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_CropPointCloud)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_EstimateNormals)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_KDTreeSearchParamKNN)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_OrientNormalsToAlignWithDirection)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_OrientNormalsTowardsCameraLocation)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_ComputePointCloudToPointCloudDistance)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_ComputePointCloudMeanAndCovariance)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_ComputePointCloudMahalanobisDistance)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_ComputePointCloudNearestNeighborDistance)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_CreatePointCloudFromFloatDepthImage)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_CreatePointCloudFromRGBDImageT)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloud, DISABLED_ConvertDepthToFloatImage)
{
    UnitTest::NotImplemented();
}
