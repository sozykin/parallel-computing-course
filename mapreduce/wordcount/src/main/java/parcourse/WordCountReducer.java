/*
 * Example of WordCount Reducer
 */
package parcourse;

import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import java.io.IOException;

public class WordCountReducer 
    extends Reducer<Text, IntWritable, Text, IntWritable> {
 
    // Reduce function 
    public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
        int sum = 0;
        // Sum up all 1
        for (IntWritable val : values) {
           sum += val.get();
        }
        // Generate pair (word, word_count)
        context.write(key, new IntWritable(sum));
    }
}


