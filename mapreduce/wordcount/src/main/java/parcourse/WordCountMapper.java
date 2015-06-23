/**
 * Example of WordCount Mapper
 */
package parcourse;

import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import java.io.IOException;
import java.util.StringTokenizer;


public class WordCountMapper
    extends Mapper<LongWritable, Text, Text, IntWritable> {

    // Hadoop wrapper for 1
    private final static IntWritable one = new IntWritable(1);
    // Hadoop wrapper for String
    private Text word = new Text();

    public void map(LongWritable key, Text value, Context 
        context) throws IOException, InterruptedException {
        // Get text line from file
        String line = value.toString();
        // Split the line into words
        StringTokenizer tokenizer = new StringTokenizer(line);
        while (tokenizer.hasMoreTokens()) {
            word.set(tokenizer.nextToken());
            // Generate pair(word, 1)
            context.write(word, one);
        } 
    }
}

