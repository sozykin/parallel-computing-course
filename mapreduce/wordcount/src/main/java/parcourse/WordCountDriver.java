/*
 * Example of Wordcount MapReduce driver
 */
package parcourse;

import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

// Main class implements Tool interface
public class WordCountDriver extends Configured implements Tool {
  public static void main(String[] args) throws Exception {
    int exitCode = ToolRunner.run(new Configuration(), new WordCountDriver(),
      args);
    System.exit(exitCode);
  }

  public int run(String[] args) throws Exception {
    if (args.length != 2) {
      System.err.printf("Usage: %s [generic options] <input> <output>\n",
          getClass().getSimpleName());
      ToolRunner.printGenericCommandUsage(System.err);
      return -1;
    }
    // Creating hadoop job
    Job job = Job.getInstance(super.getConf(), "WordCount");
    // Setting Job Jar
    job.setJarByClass(getClass());
    // Setting Mapper and Reducer Classes
    job.setMapperClass(WordCountMapper.class);
    job.setReducerClass(WordCountReducer.class);    
    // Setting output Key and Value type
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);    
    // Setting input and output formats
    job.setInputFormatClass(TextInputFormat.class);    
    job.setOutputFormatClass(TextOutputFormat.class);
    // Setting input path
    FileInputFormat.addInputPath(job, new Path(args[0]));
    // Setting output path
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
    // Running the job
    return job.waitForCompletion(true) ? 0 : 1;
  }
}

