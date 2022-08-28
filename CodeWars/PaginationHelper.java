 import java.util.List;

 public class PaginationHelper<I> {

   private List<I> collection;
   private int itemsPerPage;

   /**
    * The constructor takes in an array of items and a integer indicating how many
    * items fit within a single page
    */
   public PaginationHelper(List<I> collection, int itemsPerPage) {
     this.collection = collection;
     this.itemsPerPage = itemsPerPage;
   }
  
   /**
    * returns the number of items within the entire collection
    */
   public int itemCount() {
     return this.collection.size();
   }
  
   /**
    * returns the number of pages
    */
   public int pageCount() {
     return (int)Math.ceil(itemCount() / (double)itemsPerPage);
   }
  
   /**
    * returns the number of items on the current page. page_index is zero based.
    * this method should return -1 for pageIndex values that are out of range
    */
   public int pageItemCount(int pageIndex) {   
     if (0 <= pageIndex && pageIndex < pageCount()){
       int delta = itemCount() - pageIndex * itemsPerPage;
       return Math.min(delta, itemsPerPage);
     }
     else {
       return -1;
     }     
   }
  
   /**
    * determines what page an item is on. Zero based indexes
    * this method should return -1 for itemIndex values that are out of range
    */
   public int pageIndex(int itemIndex) {
     if (0 <= itemIndex && itemIndex < itemCount()){
       return (int)Math.ceil((itemIndex + 1) / (double)itemsPerPage) - 1;
     }
     else {
       return -1;
     }
   }
 }
