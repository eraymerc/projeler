

public class App {
    public static void main(String[] args) throws Exception {
        
        Heap heap = new Heap(6);
        heap.insert(1);
        heap.insert(3);
        heap.insert(6);
        heap.insert(5);
        heap.insert(9);
        heap.insert(8);
        heap.print();
        heap.removeMax();
        heap.print();
    }
}
