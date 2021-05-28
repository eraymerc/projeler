public class Heap {
    int[] array;
    int itemCount = 0;

    // max heap
    public Heap(int heapLength) {
        array = new int[heapLength];
    }

    public void insert(int value) {
        if (itemCount == array.length) {
            return;
        }
        array[itemCount] = value;
        buildHeap(itemCount);
        itemCount++;
    }

    // build Heap
    public void buildHeap(int loc) {
        int parent = getParent(loc);
        if (array[loc] > array[parent]) {
            // swap
            int x = array[parent];
            array[parent] = array[loc];
            array[loc] = x;

            buildHeap(parent);
        } else {
            return;
        }

    }

    public static int getParent(int loc) {
        return (loc - 1) / 2;
    }

    // remove Heap
    public void removeMax() {
        array[0] = 0;

        for (int i = 1; i < itemCount; i++) {

            array[i - 1] = array[i];


        }
        itemCount--;
        array[itemCount] = 0;
        

    }

    public static int rightChild(int loc) {
        return (loc * 2) + 2;
    }

    public static int leftChild(int loc) {
        return (loc * 2) + 1;
    }

    // print Heap
    public void print() {
        for (int i : array) {
            System.out.print(i + " , ");
        }
        System.out.print("\n");
    }

}
