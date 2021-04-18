#ifndef LISTH
#define LISTH
/* FILE NAME   : list.h
 * PURPOSE     : Header module.
 * PROGRAMMER  : Matvei Kreinin,
 * LAST UPDATE : 04.11.2020.
 * NOTE        : None.
 */

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define NDEBUG

#ifndef NDEBUG
#define VERIFICATION {                                                                                                                 \
                       int count_free = 0, count_busy = 0;                                                                             \
                       print_verification(verification(count_free, count_busy), __FILE__, __LINE__, __func__, count_free, count_busy); \
                     }
#else
#define VERIFICATION ;
#endif

enum code_error {
  all_ok = 0,
  head_tail = 1,
  next_of_prev = 2,
  prev_of_next = 3,
  size_of_list = 4,
  size_of_all_list = 5
};

namespace mk5 {
  
  template <typename data_type>
  struct vertex {
    data_type data;
    int next = -1, prev = -1;
  };

  template <typename data_type>
  class list {
  private:
    vertex<data_type>* vertex_arr = nullptr;
    int capacity = -1, size = 0;
    int head = 0, tail = 0, free = 0;

  public:

    /* Default class constructor */
    list(void)
    {
      vertex_arr = (vertex<data_type> *)calloc(1000, sizeof(vertex<data_type>)); // new vertex<data_type>[1000];
    } /* End of lList' function */

    /* Class constructor */
    list(size_t size_list) : 
      vertex_arr((vertex<data_type>*)calloc(1000, sizeof(vertex<data_type>))), 
      capacity(size_list) {

      clear();
    }/* End of 'list' constructor */

    /* Class destructor */
    ~list() {
      
      if (vertex_arr != nullptr) {
        delete[] vertex_arr;
        vertex_arr = nullptr;
      }

      capacity = head = tail = 0;
    }/* End of '`list' constructor */


   /*! Checking list for correctness
    * \param[in]  variable for counting free vertexes - int& count_free
    * \param[in]  variavle for counting busy vertexes - int& couny_busy
    * \param[out] code eror
    */
    int verification(int& count_free, int& count_busy) {

      if (vertex_arr[head].prev != 0 || vertex_arr[tail].next != 0)
        return head_tail;

      int cur_vertex = head;
      while (cur_vertex != 0) {
        if (cur_vertex != vertex_arr[vertex_arr[cur_vertex].prev].next && cur_vertex != head && size > 1)
          return next_of_prev;
        if (cur_vertex != vertex_arr[vertex_arr[cur_vertex].next].prev && cur_vertex != tail && size > 1)
          return prev_of_next;

        count_busy++;
        cur_vertex = vertex_arr[cur_vertex].next;
      }

      if (count_busy != size && tail != head)
        return size_of_list;

      int i_prev = 1;
      for (; i_prev <= capacity; i_prev++)
        count_free += (vertex_arr[i_prev].prev == -1) ? 1 : 0;

      if ((count_free + count_busy != capacity) && head != tail)
        size_of_all_list;

      return all_ok;
    }/* End of 'verification' function */


    /*! Make picture with a graphviz.
     * \param[in]  none
     * \param[out] none
     */
    int dump(void) {

      FILE* file = fopen("gr_all.dot", "wb");

      if (file == NULL)
        return 0;

      fprintf(file, "digraph G{\n");
      fprintf(file, "node [color=\"#000000\", shape=record];\n struct0 [style=\"filled\", fillcolor=\"#FF019A\"];\n  ");
      fprintf(file, "struct0 [label=\"<f1> ZERO\"];\n  ");

      fprintf(file, "node [color=\"#000000\", shape=record];\n  structzero [style=\"filled\", fillcolor=\"#FF019A\"];\n  ");
      fprintf(file, "structzero [label=\"<f1> INVALID_ZERO\"];\n  ");
      fprintf(file, "edge[color = \"white\"];\n");
      for (int i_vert = 1; i_vert <= capacity; i_vert++) {

        if (vertex_arr[i_vert].prev != -1 && size > 1 && (0
          || (i_vert != vertex_arr[vertex_arr[i_vert].prev].next && i_vert != head)
          || (i_vert != vertex_arr[vertex_arr[i_vert].next].prev && i_vert != tail)
          || (i_vert == head && i_vert != vertex_arr[vertex_arr[i_vert].next].prev)
          || (i_vert == tail && i_vert != vertex_arr[vertex_arr[i_vert].prev].next)
          )) {
          fprintf(file, "node [color=\"#000000\", shape=record];\n  struct%i [style=\"filled\", fillcolor=\"RED\"];\n  ", i_vert);
          fprintf(file, "struct%i [label=\"<f0> prev (%i)|<f1> num (%i)|<f2> next (%i)|<f3> data (",
            i_vert, vertex_arr[i_vert].prev, i_vert, vertex_arr[i_vert].next);
          std::cout << vertex_arr[i_vert].data;
          fprintf(file, ")\"];\n  ");
        }
        else if (i_vert == head || i_vert == tail) {
          fprintf(file, "node [color=\"#000000\", shape=record];\n  struct%i [style=\"filled\", fillcolor=\"#675BF4\"];\n  ", i_vert);
          fprintf(file, "struct%i [label=\"<f0> prev (%i)|<f1> num (%i)|<f2> next (%i)|<f3> data (",
            i_vert, vertex_arr[i_vert].prev, i_vert, vertex_arr[i_vert].next);
          std::cout << vertex_arr[i_vert].data;
          fprintf(file, ")\"];\n  ");
        }
        else if (vertex_arr[i_vert].next != -1 && vertex_arr[i_vert].prev != -1) {
          fprintf(file, "node [color=\"#000000\", shape=record];\n  struct%i [style=\"filled\", fillcolor=\"#89F09B\"];\n  ", i_vert);
          fprintf(file, "struct%i [label=\"<f0> prev (%i)|<f1> num (%i)|<f2> next (%i)|<f3> data (",
            i_vert, vertex_arr[i_vert].prev, i_vert, vertex_arr[i_vert].next);
          std::cout << vertex_arr[i_vert].data;
          fprintf(file, ")\"];\n  ");

        }
        else {
          fprintf(file, "node[color=\"#000000\", shape=record];\n  struct%i[style=\"filled\", fillcolor=\"#F3F372\"];\n  ", i_vert);
          fprintf(file, "struct%i [label=\"<f0> prev (%i)|<f1> num (%i)|<f2> next (%i)|<f3> data (",
            i_vert, vertex_arr[i_vert].prev, i_vert, vertex_arr[i_vert].next);
          std::cout << vertex_arr[i_vert].data;
          fprintf(file, ")\"];\n  ");
        }

        if (i_vert + 1 < capacity && vertex_arr[vertex_arr[i_vert].next].prev != -1)
          fprintf(file, "struct%i -> struct%i;\n  ", i_vert, i_vert + 1);
        else if (i_vert + 1 < capacity && vertex_arr[i_vert].prev == -1)
          fprintf(file, "struct%i -> struct%i;\n  ", i_vert, i_vert + 1);
      }

      fprintf(file, "edge[color = \"black\"];\n");

      for (int i_vert = 1; i_vert <= capacity; i_vert++) {

        if (vertex_arr[i_vert].next == -1)
          fprintf(file, "struct%i:f2 -> structzero;\n  ", i_vert);
        else
          fprintf(file, "struct%i:f2 -> struct%i:f1;\n  ", i_vert, vertex_arr[i_vert].next);
        if (vertex_arr[i_vert].prev == -1)
          fprintf(file, "struct%i:f0 -> structzero;\n  ", i_vert);
        else
          fprintf(file, "struct%i:f0 -> struct%i:f1;\n  ", i_vert, vertex_arr[i_vert].prev);
      }

      fprintf(file, "}");
      fclose(file);
      if (system("C:\\Users\\MK5\\Desktop\\MIPT\\Programming\\Graphviz\\bin\\dot.exe -Tpdf"
        " C:\\Users\\MK5\\Desktop\\MIPT\\Programming\\T04LIST\\T04LIST\\gr_all.dot "
        "> C:\\Users\\MK5\\Desktop\\MIPT\\Programming\\T04LIST\\T04LIST\\Graphs\\all_out.pdf"))
        assert(0);


      file = fopen("gr_list.dot", "wb");

      if (file == NULL)
        return 0;

      fprintf(file, "digraph G{\n  rankdir=LR;\n  node [shape=record];\n  ");
      fprintf(file, "node [color=\"#000000\", shape=record];\n  struct0 [style=\"filled\", fillcolor=\"#FF019A\"];\n  ");
      fprintf(file, "struct0 [label=\"<f1> ZERO\"];\n  ");

      for (int i_vert = 1; i_vert <= capacity; i_vert++) {

        if (vertex_arr[i_vert].prev != -1 && size > 1 && (0
          || (i_vert != vertex_arr[vertex_arr[i_vert].prev].next && i_vert != head)
          || (i_vert != vertex_arr[vertex_arr[i_vert].next].prev && i_vert != tail)
          || (i_vert == head && i_vert != vertex_arr[vertex_arr[i_vert].next].prev)
          || (i_vert == tail && i_vert != vertex_arr[vertex_arr[i_vert].prev].next)
          )) {
          fprintf(file, "node [color=\"#000000\", shape=record];\n  struct%i [style=\"filled\", fillcolor=\"RED\"];\n  ", i_vert);
          fprintf(file, "struct%i [label=\"<f0> prev (%i)|<f1> num (%i)|<f2> next (%i)|<f3> data (",
            i_vert, vertex_arr[i_vert].prev, i_vert, vertex_arr[i_vert].next);
          std::cout << vertex_arr[i_vert].data;
          fprintf(file, ")\"];\n  ");
        }
        else if (i_vert == head || i_vert == tail) {
          fprintf(file, "node [color=\"#000000\", shape=record];\n  struct%i [style=\"filled\", fillcolor=\"#675BF4\"];\n  ", i_vert);
          fprintf(file, "struct%i [label=\"<f0> prev (%i)|<f1> num (%i)|<f2> next (%i)|<f3> data (",
            i_vert, vertex_arr[i_vert].prev, i_vert, vertex_arr[i_vert].next);
          std::cout << vertex_arr[i_vert].data;
          fprintf(file, ")\"];\n  ");
        }
        else if (vertex_arr[i_vert].next != -1 && vertex_arr[i_vert].prev != -1) {
          
          fprintf(file, "node [color=\"#000000\", shape=record];\n  struct%i [style=\"filled\", fillcolor=\"#89F09B\"];\n  ", i_vert);

          fprintf(file, "struct%i [label=\"<f0> prev (%i)|<f1> num (%i)|<f2> next (%i)|<f3> data (",
            i_vert, vertex_arr[i_vert].prev, i_vert, vertex_arr[i_vert].next);
          std::cout << vertex_arr[i_vert].data;
          fprintf(file, ")\"];\n  ");
         
        }

        if (vertex_arr[i_vert].next != -1 && vertex_arr[i_vert].prev != -1) {
          fprintf(file, "struct%i:f2 -> struct%i:f1;\n  ", i_vert, vertex_arr[i_vert].next);
          fprintf(file, "struct%i:f0 -> struct%i:f1;\n  ", i_vert, vertex_arr[i_vert].prev);
        }
      }
      fprintf(file, "}");

      fclose(file);
      if (system("C:\\Users\\MK5\\Desktop\\MIPT\\Programming\\Graphviz\\bin\\dot.exe -Tpdf "
        " C:\\Users\\MK5\\Desktop\\MIPT\\Programming\\T04LIST\\T04LIST\\gr_list.dot"
        " > C:\\Users\\MK5\\Desktop\\MIPT\\Programming\\T04LIST\\T04LIST\\Graphs\\list_out.pdf"))
        assert(0);

      return 1;
    }/* End of 'dump' function*/

   /* Clear all vertexes in list (doesn't free memory).
    * \param[in]  none.
    * \param[out] none.
    */
    void clear(void) {

      vertex_arr[0].next = vertex_arr[0].prev = 0;

      size = 0;
      head = tail = 1;

      if (capacity > 1)
        free = 2;

      vertex_arr[head].next = vertex_arr[head].prev = 0;

      for (int i_free = 2; i_free <= capacity; i_free++)
        vertex_arr[i_free].next = i_free + 1;

      vertex_arr[capacity].next = -1;

      VERIFICATION;
    }/* End of 'clear' function */


    /*! Add to front of list function.
     * \param[in]  value - const data_type value
     * \param[out] none
     */
    template <typename data_type>
    int push_front(data_type& value) {

      VERIFICATION;
      if (size == 0) {
        emit(&value, head, sizeof(value));

        size++;

        return head;
      }

      if (free == -1)
        alloc_memory();

      int newpos = free;
      free = vertex_arr[free].next;

      vertex_arr[newpos].prev = 0;
      vertex_arr[newpos].next = head;
      vertex_arr[head].prev = newpos;

      emit(&value, newpos, sizeof(value));
      size++;

      head = newpos;

      VERIFICATION;
      return newpos;
    } /* End of 'push_front' function */

    /*! Add element to end of list function
     * \param[in]  value - const data_type value
     * \param[out] none.
     */
    template <typename data_type>
    int push_back(const data_type &value) {

      VERIFICATION;
      if (size == 0) {
        vertex_arr[tail].data = value;
        size++;

        return tail;
      }

      if (free == -1)
        alloc_memory();

      int newpos = free;
      free = vertex_arr[free].next;

      vertex_arr[newpos].next = 0;
      vertex_arr[newpos].prev = tail;
      vertex_arr[tail].next = newpos;

      vertex_arr[newpos].data = value;
      
      size++;

      tail = newpos;

      VERIFICATION;

      return newpos;
    }/* End of 'push_back' function */


    /*! Delete element from end of list function
     * \param[in]  none.
     * \param[out] none.
     */
    template <typename data_type>
    int pop_back(void) {

      VERIFICATION;

      if (size == 0)
        return 0;

      if (size == 1) {
        size--;

        return 1;
      }

      int new_tail = vertex_arr[tail].prev;
      vertex_arr[new_tail].next = 0;

      free = tail;
      vertex_arr[tail].next = free;
      vertex_arr[tail].prev = -1;

      
      size--;

      tail = new_tail;

      VERIFICATION;

      return 1;
    }/* End of 'pop_back' function */

    /*! Delete from front of list function.
     * \param[in]  none.
     * \param[out] none.
     */
    template <typename data_type>
    int pop_front(void) {

      VERIFICATION;

      if (size == 0)
        return 0;

      if (size == 1) {
        size--;

        return 1;
      }

      int new_head = vertex_arr[head].next;
      vertex_arr[new_head].prev = 0;

      vertex_arr[head].next = free;
      free = head;
      vertex_arr[head].prev = -1;

      size--;

      head = new_head;

      VERIFICATION;

      return 1;
    }/* End of 'pop_front' function */

    /*! Getting physical index of tail.
     * \param[in]  none.
     * \param[out] adress of tail.
     */
    int end(void) {
      return tail;
    }
    /* End of 'end' function */

    /*! Getting physical index of head.
     * \param[in]  none.
     * \param[out] adress of head.
     */
    int begin(void) {
      return head;
    }
    /* End of 'begin' function */

    
    /*! Get physical adress of element that stayed before.
     * \param[in]  pos - const size_t pos
     * \param[out] adress
     */
    template <typename data_type>
    int rback(const size_t pos) {
      return vertex_arr[pos].prev;
    }/* End of 'rback' function */

    /*! Get physical adress of element that stayed after.
     * \param[in]  pos - const size_t pos
     * \param[out] adress
     */
    template <typename data_type>
    int rfront(const size_t pos) {
      return vertex_arr[pos].next;
    }
    /* End of 'rfront' function */

    /*! Get data by logical position in list.
     * \param[in]  logical position - int pos
     * \param[out] data
     */
    template <typename data_type>
    data_type & get_data(int pos) {

      VERIFICATION;

      int cur_vertex = head;
      while (cur_vertex != 0 && pos > 0) {
        cur_vertex = vertex_arr[cur_vertex].next;
        pos--;
      }

      VERIFICATION;

      return vertex_arr[cur_vertex].data;
    }/* End of 'get_data' function */

    /*! Find logical position of value in list.
     * \param[in]  value - const data_type value
     * \param[out]
     */
    template <typename data_type>
    int get_index(const data_type & value) {

      VERIFICATION;

      int pos = head;

      while (vertex_arr[pos].data != value && pos > 0) {
        pos = vertex_arr[pos].next;
      }

      VERIFICATION;

      return pos;
    }/* End of 'get_index' function */

    /*! Insert value before of physical position.
     * \param[in]  pos of insert - const int pos
     * \param[in]  value         - const data_type value
     * \param[out] return of new position
     */
    template <typename data_type>
    int emplace_back(const int pos, const data_type & value) {

      VERIFICATION;

      if (pos < 1 || pos > capacity || vertex_arr[pos].prev == -1)
        return -1;

      if (pos == head)
        return push_front(value);

      if (free == -1)
        alloc_memory();

      int newpos = free;
      free = vertex_arr[free].next;

      vertex_arr[newpos].next = pos;
      vertex_arr[vertex_arr[pos].prev].next = newpos;
      vertex_arr[newpos].prev = vertex_arr[pos].prev;
      vertex_arr[pos].prev = newpos;

      emit(&value, newpos, sizeof(value));
      size++;

      VERIFICATION;

      return newpos;
    }/* End of 'emplace_back' function */

    /*! Insert value after of physical position.
     * \param[in]  pos of insert - const int pos
     * \param[in]  value         - const data_type value
     * \param[out] return of new position
     */
    template <typename data_type>
    int emplace_front(const int pos, const data_type & value) {

      VERIFICATION;

      if (pos < 1 || pos > capacity || vertex_arr[pos].prev == -1)
        return -1;

      if (pos == tail)
        return push_back(value);

      if (free == -1)
        alloc_memory();

      int newpos = free;
      free = vertex_arr[free].next;

      vertex_arr[newpos].prev = pos;
      vertex_arr[newpos].next = vertex_arr[pos].next;
      vertex_arr[vertex_arr[pos].next].prev = newpos;
      vertex_arr[pos].next = newpos;

      emit(&value, newpos, sizeof(value));
      size++;

      VERIFICATION;

      return newpos;
    }/* End of 'emplace_front' function */
   
    /*! Delete value after of physical position.
     * \param[in]  pos of delete - const int pos
     * \param[out] code error
     */
    template <typename data_type>
    int pop_pos_front(const int pos) {

      VERIFICATION;

      if (pos < 1 || pos > capacity || vertex_arr[pos].prev == -1)
        return -1;

      if (pos == tail)
        return 0;

      int next = vertex_arr[pos].next;

      if (next == tail) {
        pop_back();

        return 1;
      }

      vertex_arr[pos].next = vertex_arr[next].next;
      vertex_arr[vertex_arr[next].next].prev = pos;

      vertex_arr[next].next = free;
      vertex_arr[next].prev = -1;
      free = next;
      size--;

      VERIFICATION;

      return 1;
    }/* End of 'pop_pos_front' function */

    /*! Delete value before of physical position.
     * \param[in]  pos of delete - const int pos
     * \param[out] code error
     */
    template <typename data_type>
    int pop_pos_back(const int pos) {

      VERIFICATION;

      if (pos == head)
        return 0;

      if (pos < 1 || pos > capacity || vertex_arr[pos].prev == -1)
        return -1;

      int prev = vertex_arr[pos].prev;

      if (prev == head) {
        pop_front();

        return 1;
      }

      vertex_arr[vertex_arr[prev].prev].next = pos;
      vertex_arr[pos].prev = vertex_arr[prev].prev;

      vertex_arr[prev].next = free;
      free = prev;

      vertex_arr[prev].prev = -1;
      size--;

      VERIFICATION;

      return 1;
    }
    /* End of 'pop_pos_back' function */

    /*! Delete current value of physical position.
     * \param[in]  pos of delete - const int pos
     * \param[out] code error
     */
    template <typename data_type>
    int pop_pos(const int pos) {

      VERIFICATION;

      if (pos < 1 || pos > capacity || vertex_arr[pos].prev == -1)
        return -1;

      if (pos == head) {
        pop_front();

        return 1;
      }
      if (pos == tail) {
        pop_back();

        return 1;
      }
      int next = vertex_arr[pos].next;
      int prev = vertex_arr[pos].prev;

      vertex_arr[next].prev = prev;
      vertex_arr[prev].next = next;

      vertex_arr[pos].next = free;
      free = pos;

      vertex_arr[pos].prev = -1;
      size--;

      VERIFICATION;

      return 1;
    }/* End of 'pop_pos' function */

    /*! Return size of list
     * \param[in]  none.
     * \param[out] size of list.
     */
    int get_size(void) {
      return size;
    }/* End of 'get_size' function */

    /*! Return capacity of list
     * \param[in]  none.
     * \param[out] capacity of list
     */
    int get_capacity(void) {
      return capacity;
    }/* End of 'get_capacity' function */

  private:

    /* Allocate some memory for the list.
     * \param[in]  none.
     * \param[out] none.
     */
    //template <typename data_type>
    int alloc_memory(void)
    {
      if (free != -1)
        return 0;
      if (capacity <= 0)
        return 0;

      capacity *= 2;
      //vertex_arr = (vertex<data_type> *)calloc(1000, sizeof(vertex<data_type>));
        //(vertex<data_type> *)realloc(vertex_arr, capacity * sizeof(vertex<data_type>));

      return 1;
    }/* End of 'alloc_memory' function */

   /* Check the value for correcntess.
    * \brief
    * \version
    * \authors
    * \param[in]  value - const data_type& value
    * \param[out] true or false
    */
    template <typename data_type>
    int IsValue(const data_type & value) {

      return false;//  isnan(value);
    }/* End of 'IsValue' function */

    /*! Add vertex to list of free vertexes.
     * \param[in]  physical position - const int pos
     * \param[out] none.
     */
    template <typename data_type>
    int free_vertex(const int pos) {

      vertex_arr[pos].prev = -1;

      if (free == -1)
        vertex_arr[pos].next = -1;
      else
        vertex_arr[pos].next = free;

      free = pos;

      return 1;
    }/* End of 'free_vertex' function */

    /* Add data to the vertex.
     * \param[in]  data for add      - const void* data
     * \param[in]  physical position - const int pos
     * \param[in]  size of data      - const int size_of
     * \param[out] none.
     */
    template <typename data_type>
    int emit(const void* data, const int pos, const int size_of) {

      char* element = (char*)data;
      memcpy(&(vertex_arr[pos].data), element, size_of);

      return 1;
    }/* End of 'emit' function */

    /*! Print code error and what it is problem.
     * \param[in]  code of error                     - int code_error
     * \param[in]  file where triggered verification - const char* file
     * \param[in]  line where triggered verification - const int line
     * \param[in]  num of free vertexes              - const int count_free
     * \param[in]  num of busy vertexes              - const int count_busy
     * \param[out] none
     */
    void print_verification(const int code_error, const char* file, const int line, const char* func, const int count_free, const int count_busy) {


      switch (code_error) {
      case head_tail:
        fprintf(stderr, "Something is going wrong and your head or tail doesn't point on zero element.\n"
          "View the picture of graph.\n");

        break;
      case next_of_prev:
        fprintf(stderr, "Your graph is broken. (next of prev != cur).\n"
          "You need to check more information in picture\n");

        break;
      case prev_of_next:
        fprintf(stderr, "Your graph is broken.(prev of next != cur).\n"
          "You need to check more information in picture\n");

        break;
      case size_of_list:
        fprintf(stderr, "You have problems with a size of graph!\n"
          "Size (%i), size that counted by me (%i)\n", size, count_busy);

        break;
      case size_of_all_list:
        fprintf(stderr, "Your graph is broken. (count of free and busy elements not equal capacity).\n"
          "You need to check more information in picture\n"
          "Size (%i), size that counted by me (%i)", count_free + count_busy, size);

        break;
      default:
        return;
      }
      fprintf(stderr, "FILE: %s\nLINE: %i\nFUNC: %s\n", file, line, func);
      dump();
      getchar();
      abort();

    }/* End of 'print_ferivication*/
  };
  
  /* Comparing two vertexes, that function needed for sorting elements by indexes.
   * \param[in]  first vertex  - const mk5::vertex& first
   * \param[in]  second vertex - const mk5::vertex& second
   * \param[out] return -1 if (first > second)
   *             return  1 if (first < second)
   */
  template <typename type_data>
  int compare_vertex(const type_data* first, const type_data* second) {

    if (second->prev == -1 && first->prev == -1)
      return 0;

    if (second->prev == -1)
      return -1;

    if (first->prev == -1)
      return 1;

    return first->next - second->next;
  }/* End of 'compare_vertex' function */


}

#endif