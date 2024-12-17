#include "list.h"
#include "gtest.h"



TEST(list_tests, can_create_void_node)
{
    ASSERT_NO_THROW (List<int> zxc);
}

TEST(list_tests, can_create_node_data)
{
    Node <int>* test = new Node <int>;
    Node <int> zxc(27,test);
    EXPECT_EQ (27, zxc.data);
}

TEST(list_tests, can_create_node_ref)
{
    Node <int>* test = new Node <int>;
    Node <int> zxc(27,test);
    EXPECT_EQ (zxc.next, test);
}

TEST(list_tests, can_compare1)
{
    Node <int> zxc1(15);
    Node <int> zxc2(15);
    EXPECT_EQ (zxc1, zxc2);
}

TEST(list_tests, can_compare2)
{
    Node <int> zxc1(15);
    Node <int> zxc2(29);
    EXPECT_NE (zxc1, zxc2);
}

TEST(iterators_tests, can_strelochka___assign__NE__inc_post_pref )
{
    const int k = 15;
    List <int> zxc(k);
    int zxc1;
    for (auto i = zxc.begin(); i != zxc.end(); i++)
    {
       zxc1 = i -> data;
    }
    EXPECT_EQ(zxc1, k);
}

TEST(iterators_tests, compare)
{
    const int k = 15;
    List <int> zxc(k);
    zxc.InsertToTail(11);
    auto i = zxc.begin();
    auto b = zxc.tail();
    i++;
    EXPECT_EQ(b, i);
    
}

/// test on list

TEST(lists_tests, can_create_empty_list)
{
    List<int> zxc;
    EXPECT_EQ(zxc.isEmpty(), 1);
}

TEST(lists_tests, can_create_NOempty_list)
{
    List<int> zxc(37);
    EXPECT_EQ(zxc.ViewTail(), 37);
}

TEST(lists_tests, check_Nempty)
{
    List<int> zxc(37);
    EXPECT_EQ(!zxc.isEmpty(), 1);
}

TEST(lists_tests, check_empty)
{
    List<int> zxc;
    EXPECT_EQ(zxc.isEmpty(), 1);
}

TEST(lists_tests, insert_head1)
{
    List<int> zxc;
    zxc.InsertToHead(15);
    zxc.InsertToHead(32);
    EXPECT_EQ(zxc.ViewHead(), 32);
}

TEST(lists_tests, insert_head2)
{
    List<int> zxc;
    zxc.InsertToHead(15);
    zxc.InsertToHead(32);
    EXPECT_EQ(zxc.ViewTail(), 15);
}

TEST(lists_tests, insert_to_tail1)
{
    List<int> zxc;
    zxc.InsertToTail(15);
    zxc.InsertToTail(32);
    EXPECT_EQ(zxc.ViewTail(), 32);
}

TEST(lists_tests, insert_to_tail2)
{
    List<int> zxc;
    zxc.InsertToTail(15);
    zxc.InsertToTail(32);
    EXPECT_EQ(zxc.ViewHead(), 15);
}

TEST(lists_tests, check_one_time_delete1)
{
    List <int> zxc(2);
    zxc.InsertToTail(12);
    zxc.InsertToTail(15);
    zxc.InsertToTail(2);
    zxc.InsertToTail(37);
    zxc.Delete(2);
    EXPECT_EQ(zxc.ViewHead(), 12);


}

TEST(lists_tests, check_one_time_delete2)
{
    List <int> zxc(2);
    zxc.InsertToTail(12);
    zxc.InsertToTail(15);
    zxc.InsertToTail(2);
    zxc.InsertToTail(37);
    zxc.Delete(2);
    auto a = zxc.begin();
    a++; a++;
    EXPECT_EQ(a -> data, 2);


}

TEST(lists_tests, check_one_time_delete3)
{
    List <int> zxc(2);
    zxc.InsertToTail(12);
    zxc.InsertToTail(15);
    zxc.InsertToTail(2);
    zxc.InsertToTail(37);
    zxc.Delete(37);
    EXPECT_EQ(zxc.ViewTail(), 2);
}

TEST(lists_tests, check_one_time_delete4)
{
    List <int> zxc(2);
    zxc.Delete(2); 
    List <int> zxc1;
    EXPECT_EQ(zxc1, zxc);
}

TEST(lists_tests, constructor_copy)
{
    List <int> zxc;
    for (int i = 0; i < 20 ; i++)
    {
        zxc.InsertToTail(i);
    }
    List <int> zxc1(zxc);
    EXPECT_EQ(zxc,zxc1);
}

TEST(lists_tests, assign_list1)
{
    List <int> zxc;
    for (int i = 0; i < 20 ; i++)
    {
        zxc.InsertToTail(i);
    }
    List <int> zxc1 = zxc;
    EXPECT_EQ(zxc,zxc1);
}

TEST(lists_tests, assign_list2)
{
    List <int> zxc;
    List <int> zxc1;
    for (int i = 0; i < 35 ; i++)
    {
        zxc.InsertToTail(i);
    }

    for (int i = 0; i < 20 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    zxc1 = zxc;
    EXPECT_EQ(zxc,zxc1);
}

TEST(lists_tests, assign_list3)
{
    List <int> zxc;
    List <int> zxc1;
    for (int i = 0; i < 35 ; i++)
    {
        zxc1.InsertToTail(i);
    }

    for (int i = 0; i < 20 ; i++)
    {
        zxc.InsertToTail(i);
    }
    zxc1 = zxc;
    EXPECT_EQ(zxc,zxc1);
}

TEST(lists_tests, can_clean)
{
    List <int> zxc;
    for (int i = 0; i < 35 ; i++)
    {
        zxc.InsertToTail(i);
    }
    zxc.Clean();
    List <int> zxc1;
    EXPECT_EQ(zxc, zxc1);
}

TEST(lists_tests, can_insert_after1)
{
    List <int> zxc;
    auto a = zxc.begin();
    for (int i = 0; i < 21 ; i++)
    {
        zxc.InsertToTail(i);
        if(i == 10) a = zxc.tail();
    }
    zxc.InsertAfter(a, 999);
    a++;
    EXPECT_EQ(a -> data, 999);

}

TEST(lists_tests, can_insert_after2)
{
    List <int> zxc;
    for (int i = 0; i < 21 ; i++)
    {
        zxc.InsertToTail(i);
    }
    auto a = zxc.tail();
    zxc.InsertAfter(a, 999);
    EXPECT_EQ(zxc.ViewTail(), 999);
}

TEST(lists_tests, search_true)
{
    List <int> zxc;
    auto a = zxc.begin();
    for (int i = 0; i < 21 ; i++)
    {
        zxc.InsertToTail(i);
        if(i == 19) a = zxc.tail();
    }
    EXPECT_EQ(a, zxc.Search(19));
    

}

TEST(lists_tests, search_false)
{
    List <int> zxc;
    for (int i = 0; i < 21 ; i++)
    {
        zxc.InsertToTail(i);
    }
    EXPECT_EQ(zxc.end(), zxc.Search(1948));
}

TEST(lists_tests, can_delete_po_it1)
{
    List <int> zxc;
    auto a = zxc.begin();
    for (int i = 0; i < 21 ; i++)
    {
        zxc.InsertToTail(i);
        if(i == 19) a = zxc.tail();
    }
    zxc.Delete(a);
    EXPECT_EQ(zxc.Search(19), zxc.end());

}

TEST(lists_tests, can_delete_po_it2)
{
    List <int> zxc;
    for (int i = 0; i < 21 ; i++)
    {
        zxc.InsertToTail(i);
    }
    auto a = zxc.begin();
    zxc.Delete(a);
    EXPECT_EQ(zxc.Search(0), zxc.end());

}

TEST(lists_tests, can_delete_po_it3)
{
    List <int> zxc;
    for (int i = 0; i < 21 ; i++)
    {
        zxc.InsertToTail(i);
    }
    auto a = zxc.tail();
    zxc.Delete(a);
    EXPECT_EQ(zxc.Search(20), zxc.end());
    
}


/////////////////////////

TEST(lists_tests, can_delete_po_double_it1)
{
    List <int> zxc;
    for (int i = 0; i < 21 ; i++)
    {
        zxc.InsertToTail(i);
    }
    auto a = zxc.begin();
    auto b = zxc.begin();
    ++b;
    ++b;
    ++b;
    zxc.Delete(a, b);
    List <int> zxc1;
    for (int i = 3; i < 21 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    
    EXPECT_EQ(zxc, zxc1);
    
}

TEST(lists_tests, can_delete_po_double_it2)
{
    List <int> zxc;
    for (int i = 0; i < 21 ; i++)
    {
        zxc.InsertToTail(i);
    }
    auto a = zxc.begin();
    auto b = zxc.end();
    for (int i = 0; i < 10; i++) a++;
    zxc.Delete(a, b);
    List <int> zxc1;
    for (int i = 0; i < 10 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    EXPECT_EQ(zxc, zxc1);
    
}

TEST(lists_tests, can_delete_po_double_it3)
{
    List <int> zxc;
    for (int i = 0; i < 21 ; i++)
    {
        zxc.InsertToTail(i);
    }
    zxc.Delete(zxc.begin(), zxc.end());
    List <int> zxc1;
    EXPECT_EQ(zxc, zxc1);
}

TEST(lists_tests, throw_delete_po_double_it4)
{
    List <int> zxc;
    for (int i = 0; i < 21 ; i++)
    {
        zxc.InsertToTail(i);
    }
    ASSERT_ANY_THROW(zxc.Delete(zxc.end(), zxc.begin()));
}

TEST(lists_tests, deletall)
{
    List <int> zxc(10);
    for (int i = 0; i < 21 ; i++)
    {
        zxc.InsertToTail(i);
    }
    zxc.InsertToTail(10);
    zxc.DeleteAll(10);
    List <int> zxc1;
    for (int i = 0; i < 21 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    zxc1.Delete(10);
    EXPECT_EQ(zxc, zxc1);

}

TEST(lists_tests, inverse)
{
    List <int> zxc;
    for (int i = 0; i < 10 ; i++)
    {
        zxc.InsertToTail(i);
    }

    List <int> zxc1;
    for (int i = 9; i > -1 ; i--)
    {
        zxc1.InsertToTail(i);
    }
    zxc.Inverse();
    
    EXPECT_EQ(zxc, zxc1);
}

TEST(lists_tests, merge1)
{
    List <int> zxc;
    for (int i = 0; i < 10 ; i++)
    {
        zxc.InsertToTail(i);
    }

    List <int> zxc1;
    for (int i = 10; i < 21 ; i++)
    {
        zxc1.InsertToTail(i);
    }

    List <int> zxc3;
    for (int i = 0; i < 21 ; i++)
    {
        zxc3.InsertToTail(i);
    }
    
    EXPECT_EQ(zxc.Merge(zxc.tail(),zxc1), zxc3);

}

TEST(lists_tests, merge2)////
{
    List <int> zxc;
    auto a = zxc.begin();
    for (int i = 0; i < 10 ; i++)
    {
        zxc.InsertToTail(i);
        if (i == 5) a = zxc.tail();
    }

    List <int> zxc1;
    for (int i = 10; i < 21 ; i++)
    {
        zxc1.InsertToTail(i);
    }

    List <int> zxc3;
    for (int i = 0; i < 6 ; i++)
    {
        zxc3.InsertToTail(i);
    }
    for (int i = 6; i < 17 ; i++)
    {
        zxc3.InsertToTail(i+4);
    }
    for (int i = 6; i < 10 ; i++)
    {
        zxc3.InsertToTail(i);
    }
    
    EXPECT_EQ(zxc.Merge(a,zxc1), zxc3);
}

TEST(lists_tests, merge3)
{
    List <int> zxc;
    for (int i = 0; i < 10 ; i++)
    {
        zxc.InsertToTail(i);
    }

    List <int> zxc1;
    for (int i = 10; i < 21 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    ASSERT_ANY_THROW(zxc.Merge(zxc.end(),zxc1));
}

/////
TEST(lists_tests, mergewith1)
{
    List <int> zxc;
    for (int i = 0; i < 10 ; i++)
    {
        zxc.InsertToTail(i);
    }

    List <int> zxc1;
    for (int i = 10; i < 21 ; i++)
    {
        zxc1.InsertToTail(i);
    }

    List <int> zxc3;
    for (int i = 0; i < 21 ; i++)
    {
        zxc3.InsertToTail(i);
    }
    zxc.MergeWith(zxc.tail(),zxc1);
    EXPECT_EQ(zxc, zxc3);

}

TEST(lists_tests, mergewith2)
{
    List <int> zxc;
    auto a = zxc.begin();
    for (int i = 0; i < 10 ; i++)
    {
        zxc.InsertToTail(i);
        if (i == 5) a = zxc.tail();
    }

    List <int> zxc1;
    for (int i = 10; i < 21 ; i++)
    {
        zxc1.InsertToTail(i);
    }

    List <int> zxc3;
    for (int i = 0; i < 6 ; i++)
    {
        zxc3.InsertToTail(i);
    }
    for (int i = 6; i < 17 ; i++)
    {
        zxc3.InsertToTail(i+4);
    }
    for (int i = 6; i < 10 ; i++)
    {
        zxc3.InsertToTail(i);
    }
    zxc.MergeWith(a,zxc1);
    EXPECT_EQ(zxc, zxc3);
}

TEST(lists_tests, mergewith3)
{
    List <int> zxc;
    for (int i = 0; i < 10 ; i++)
    {
        zxc.InsertToTail(i);
    }

    List <int> zxc1;
    for (int i = 10; i < 21 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    ASSERT_ANY_THROW(zxc.MergeWith(zxc.end(),zxc1));
}

TEST(lists_tests, made_uniq)
{
    List <int> zxc(5);
    for (int i = 0; i < 10 ; i++)
    {
        zxc.InsertToTail(i);
    }
    zxc.InsertToTail(5);
    zxc.MadeUnique();

    List <int> zxc1;
    for (int i = 0; i < 10 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    zxc1.Delete(5);
    zxc1.InsertToTail(5);
    EXPECT_EQ(zxc, zxc1);
}

TEST(lists_tests, cycle_test1)
{
    List <int> zxc1;
    for (int i = 0; i < 10 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    EXPECT_EQ(zxc1.Cycle(), 0);
}



/////
TEST(lists_tests, cycle_test2)
{
    List <int> zxc1;
    for (int i = 0; i < 11 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    zxc1.tail() -> next = zxc1.begin() -> next;
    EXPECT_EQ(zxc1.Cycle(), true);
}



TEST(lists_tests, break_cycle_test)
{
    List <int> zxc1;
    for (int i = 0; i < 10 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    zxc1.tail() -> next = zxc1.begin() -> next;

    zxc1.BreakCycle();
    EXPECT_EQ(zxc1.Cycle(), 0);

}

TEST(lists_tests, to_string)
{
    List <int> zxc1;
    for (int i = 0; i < 3 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    EXPECT_EQ(zxc1.ToString(),"0; 1; 2");


}

TEST(lists_tests, get_size1)
{
     List <int> zxc1;
    for (int i = 0; i < 3 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    EXPECT_EQ(zxc1.GetSize(), 3);
}

TEST(lists_tests, get_size2)
{
    List <int> zxc1;
    EXPECT_EQ(zxc1.GetSize(), 0);

}

TEST(lists_tests, Merge)
{
    List <int> zxc;
    for (int i = 0; i < 11 ; i++)
    {
        zxc.InsertToTail(i);
    }
    List <int> zxc1;
    for (int i = 11; i < 21 ; i++)
    {
        zxc1.InsertToTail(i);
    }

    List <int> zxc2;
    for (int i = 0; i < 21 ; i++)
    {
        zxc2.InsertToTail(i);
    }
    List <int> zxc3 = zxc.Merge(zxc1);
    EXPECT_EQ(zxc3, zxc2);


}

TEST(lists_tests, equal_operator)
{
    List <int> zxc;
    for (int i = 0; i < 11 ; i++)
    {
        zxc.InsertToTail(i);
    }

    List <int> zxc1;
    for (int i = 0; i < 11 ; i++)
    {
        zxc1.InsertToTail(i);
    }
    EXPECT_EQ(zxc, zxc1);
}





