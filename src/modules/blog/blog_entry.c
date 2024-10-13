#define _XOPEN_SOURCE 700 // Define POSIX.1-2008 compliance level

#include "../../api/blog_entry_items.h"
#include "../../include/generate_url_theme.h"
#include "../../include/log.h"
#include "../../include/read_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *blog_entry(const char *id, int epoch) {
  // Get templates
  char *filename_blog_container_html =
      generate_url_theme("blog/blog-container_epoch%d.html", epoch);
  const char *blog_container_html =
      read_file_to_string(filename_blog_container_html);
  free(filename_blog_container_html);

  char *filename_blog_entry_html =
      generate_url_theme("blog/blog-entry_epoch%d.html", epoch);
  const char *blog_entry_html = read_file_to_string(filename_blog_entry_html);
  free(filename_blog_entry_html);

  // Get elements templates
  char *filename_element_paragraph_html =
      generate_url_theme("elements/paragraph/paragraph_epoch%d.html", epoch);
  const char *element_paragraph_html =
      read_file_to_string(filename_element_paragraph_html);
  free(filename_element_paragraph_html);

  char *filename_element_tittle_html =
      generate_url_theme("elements/tittle/tittle_epoch%d.html", epoch);
  const char *element_tittle_html =
      read_file_to_string(filename_element_tittle_html);
  free(filename_element_tittle_html);

  char *filename_element_image_html =
      generate_url_theme("elements/image/image_epoch%d.html", epoch);
  const char *element_image_html =
      read_file_to_string(filename_element_image_html);
  free(filename_element_image_html);

  char *filename_element_image_gallery_html = generate_url_theme(
      "elements/image-gallery/image-gallery_epoch%d.html", epoch);
  const char *element_image_gallery_html =
      read_file_to_string(filename_element_image_gallery_html);
  free(filename_element_image_gallery_html);

  /////////////////////////
  char *filename_element_gallery_container_html = generate_url_theme(
      "elements/gallery/gallery-container_epoch%d.html", epoch);
  const char *element_gallery_container_html =
      read_file_to_string(filename_element_gallery_container_html);
  free(filename_element_gallery_container_html);

  char *filename_element_gallery_row_html =
      generate_url_theme("elements/gallery/gallery-row_epoch%d.html", epoch);
  const char *element_gallery_row_html =
      read_file_to_string(filename_element_gallery_row_html);
  free(filename_element_gallery_row_html);

  char *filename_element_gallery_item_html =
      generate_url_theme("elements/gallery/gallery-item_epoch%d.html", epoch);
  const char *element_gallery_item_html =
      read_file_to_string(filename_element_gallery_item_html);
  free(filename_element_gallery_item_html);

  /////////////////////////

  char *filename_element_image_paragraph_html = generate_url_theme(
      "elements/image-paragraph/image-paragraph_epoch%d.html", epoch);
  const char *element_image_paragraph_html =
      read_file_to_string(filename_element_image_paragraph_html);
  free(filename_element_image_paragraph_html);

  char *filename_element_date_time_html =
      generate_url_theme("elements/date-time/date-time_epoch%d.html", epoch);
  const char *element_date_time_html =
      read_file_to_string(filename_element_date_time_html);
  free(filename_element_date_time_html);

  char *filename_element_link_html =
      generate_url_theme("elements/link/link_epoch%d.html", epoch);
  const char *element_link_html =
      read_file_to_string(filename_element_link_html);
  free(filename_element_link_html);

  char *filename_element_byline_html =
      generate_url_theme("elements/byline/byline_epoch%d.html", epoch);
  const char *element_byline_html =
      read_file_to_string(filename_element_byline_html);
  free(filename_element_byline_html);

  if (!blog_container_html || !blog_entry_html || !element_paragraph_html ||
      !element_tittle_html || !element_image_html ||
      !element_image_gallery_html || !element_image_paragraph_html ||
      !element_date_time_html || !element_link_html || !element_byline_html ||
      !element_gallery_container_html || !element_gallery_row_html ||
      !element_gallery_item_html) {
    perror("Failed to load HTML templates");
    // Free allocated templates if any
    if (blog_container_html)
      free((void *)blog_container_html);
    if (blog_entry_html)
      free((void *)blog_entry_html);
    if (element_paragraph_html)
      free((void *)element_paragraph_html);
    if (element_tittle_html)
      free((void *)element_tittle_html);
    if (element_image_html)
      free((void *)element_image_html);
    if (element_image_paragraph_html)
      free((void *)element_image_paragraph_html);
    if (element_date_time_html)
      free((void *)element_date_time_html);
    if (element_link_html)
      free((void *)element_link_html);
    if (element_byline_html)
      free((void *)element_byline_html);
    if (element_image_gallery_html)
      free((void *)element_image_gallery_html);
    if (element_gallery_container_html)
      free((void *)element_gallery_container_html);
    if (element_gallery_row_html)
      free((void *)element_gallery_row_html);
    if (element_gallery_item_html)
      free((void *)element_gallery_item_html);
    return NULL;
  }

  // Get blog list
  int BlogEntryItemsCount = 0;
  BlogEntryItems *home_blog_items = getBlogEntryItems(id, &BlogEntryItemsCount);
  if (home_blog_items == NULL) {
    perror("Failed to load blog items");
    free((void *)blog_container_html);
    free((void *)blog_entry_html);
    free((void *)element_paragraph_html);
    free((void *)element_tittle_html);
    free((void *)element_image_html);
    free((void *)element_image_paragraph_html);
    free((void *)element_date_time_html);
    free((void *)element_link_html);
    free((void *)element_byline_html);
    free((void *)element_image_gallery_html);
    free((void *)element_gallery_container_html);
    free((void *)element_gallery_row_html);
    free((void *)element_gallery_item_html);
    return NULL;
  }

  // Buffer to hold all items
  char *itemsBuffer = NULL;
  size_t itemsBufferSize = 0;

  // Generate the blog items
  for (int i = 0; i < BlogEntryItemsCount; i++) {
    char itemBuffer[20480]; // Buffer to hold a single item
    int itemLength = 0;
    if (strcmp(home_blog_items[i].type, "paragraph") == 0) {
      itemLength =
          snprintf(itemBuffer, sizeof(itemBuffer), element_paragraph_html,
                   home_blog_items[i].extra_data, home_blog_items[i].content);
    } else if (strcmp(home_blog_items[i].type, "tittle") == 0) {
      itemLength =
          snprintf(itemBuffer, sizeof(itemBuffer), element_tittle_html,
                   home_blog_items[i].extra_data, home_blog_items[i].content);
    } else if (strcmp(home_blog_items[i].type, "image") == 0) {
      itemLength =
          snprintf(itemBuffer, sizeof(itemBuffer), element_image_html,
                   home_blog_items[i].content, home_blog_items[i].extra_data);
    } else if (strcmp(home_blog_items[i].type, "image-gallery") == 0) {
      itemLength =
          snprintf(itemBuffer, sizeof(itemBuffer), element_image_gallery_html,
                   home_blog_items[i].content, home_blog_items[i].content,
                   home_blog_items[i].extra_data);
    } else if (strcmp(home_blog_items[i].type, "image-paragraph") == 0) {
      itemLength =
          snprintf(itemBuffer, sizeof(itemBuffer), element_image_paragraph_html,
                   home_blog_items[i].content, home_blog_items[i].extra_data);
    } else if (strcmp(home_blog_items[i].type, "date-time") == 0) {
      itemLength =
          snprintf(itemBuffer, sizeof(itemBuffer), element_date_time_html,
                   home_blog_items[i].extra_data, home_blog_items[i].content);
    } else if (strcmp(home_blog_items[i].type, "link") == 0) {
      itemLength =
          snprintf(itemBuffer, sizeof(itemBuffer), element_link_html,
                   home_blog_items[i].extra_data, home_blog_items[i].content);
    } else if (strcmp(home_blog_items[i].type, "byline") == 0) {
      itemLength =
          snprintf(itemBuffer, sizeof(itemBuffer), element_byline_html,
                   home_blog_items[i].content, home_blog_items[i].extra_data);
    } else if (strcmp(home_blog_items[i].type, "gallery") == 0) {
      char *image;
      int columns;
      int image_width;
      int table_width;

      int counter = 0;
      int image_count = 0;
      char *images;

      // Allocate memory for images
      images = malloc(strlen(home_blog_items[i].content) +
                      1); // Allocate enough memory
      if (images == NULL) {
        LOG_ERROR("Failed to allocate memory");
      }

      // Copy the content of home_blog_items[i].content
      strcpy(images, home_blog_items[i].content);

      // Count the number of images (separated by ;)
      image = strtok(images, ";");
      while (image != NULL) {
        image_count++;
        image = strtok(NULL, ";");
      }

      // Determine the number of columns based on the number of images
      if (image_count == 1) {
        columns = 1;
        image_width = 500;
        table_width = 100;
      } else if (image_count == 2) {
        columns = 2;
        image_width = 200;
        table_width = 50;
      } else if (image_count == 3) {
        columns = 3;
        image_width = 150;
        table_width = 33;
      } else if (image_count == 4) {
        columns = 2;
        image_width = 200;
        table_width = 50;
      } else {
        columns = 3;
        image_width = 150;
        table_width = 33;
      }

      LOG_DEBUG("Number of columns: %i", columns);
      LOG_DEBUG("Image width: %i px", image_width);
      LOG_DEBUG("Table width: %i", table_width);

      // Buffers to store the results
      // Final buffer that will contain the complete table
      char tableBuffer[4096] = "";
      char rowBuffer[1024];              // Temporary buffer for rows
      char cellBuffer[512];              // Temporary buffer for each cell
      char rowsContentBuffer[2048] = ""; // Stores all the rows

      // Reset the images to traverse them again
      strcpy(images, home_blog_items[i].content);

      // Use strtok to split the string by the ';' delimiter
      image = strtok(images, ";");

      // Traverse each image
      while (image != NULL) {
        // If counter is 0 or a multiple of columns, prepare a new row
        if (counter % columns == 0) {
          // Clear the row buffer for each new row
          rowBuffer[0] = '\0';
        }

        // Prepare the cell content using the template for each image
        snprintf(cellBuffer, sizeof(cellBuffer), element_gallery_item_html,
                 table_width, image, image, image_width);

        // Concatenate the cell content to the row
        strcat(rowBuffer, cellBuffer);

        counter++;

        // If the counter is a multiple of columns, close the row
        if (counter % columns == 0) {
          // Add the row to the general content of rows
          char completeRow[1024];
          snprintf(completeRow, sizeof(completeRow), element_gallery_row_html,
                   rowBuffer);
          strcat(rowsContentBuffer, completeRow);
        }

        // Continue with the next token (image)
        image = strtok(NULL, ";");
      }

      // If the last row is not complete, add it anyway
      if (counter % columns != 0) {
        char completeRow[1024];
        snprintf(completeRow, sizeof(completeRow), element_gallery_row_html,
                 rowBuffer);
        strcat(rowsContentBuffer, completeRow);
      }

      // Print the final result
      LOG_DEBUG("%s\n", tableBuffer);

      itemLength = snprintf(itemBuffer, sizeof(itemBuffer),
                            element_gallery_container_html, rowsContentBuffer);
    }

    if (itemLength < 0) {
      perror("Error formatting item");
      free(itemsBuffer);
      free(home_blog_items);
      free((void *)blog_container_html);
      free((void *)blog_entry_html);
      free((void *)element_paragraph_html);
      free((void *)element_tittle_html);
      free((void *)element_image_html);
      free((void *)element_image_paragraph_html);
      free((void *)element_date_time_html);
      free((void *)element_link_html);
      free((void *)element_byline_html);
      free((void *)element_image_gallery_html);
      free((void *)element_gallery_container_html);
      free((void *)element_gallery_row_html);
      free((void *)element_gallery_item_html);
      return NULL;
    }

    // Reallocate memory for itemsBuffer
    char *tempBuffer = realloc(itemsBuffer, itemsBufferSize + itemLength +
                                                1); // +1 for null terminator
    if (tempBuffer == NULL) {
      perror("Failed to allocate memory for itemsBuffer");
      free(itemsBuffer);
      free(home_blog_items);
      free((void *)blog_container_html);
      free((void *)blog_entry_html);
      free((void *)element_paragraph_html);
      free((void *)element_tittle_html);
      free((void *)element_image_html);
      free((void *)element_image_paragraph_html);
      free((void *)element_date_time_html);
      free((void *)element_link_html);
      free((void *)element_byline_html);
      free((void *)element_image_gallery_html);
      free((void *)element_gallery_container_html);
      free((void *)element_gallery_row_html);
      free((void *)element_gallery_item_html);
      return NULL;
    }

    itemsBuffer = tempBuffer;

    // Copy the new item into itemsBuffer
    memcpy(itemsBuffer + itemsBufferSize, itemBuffer, itemLength);
    itemsBufferSize += itemLength;
    itemsBuffer[itemsBufferSize] = '\0'; // Null-terminate the string
  }

  // Allocate buffer for the full HTML content
  size_t contentBufferSize =
      snprintf(NULL, 0, blog_container_html, itemsBuffer) +
      1; // +1 for null terminator
  char *contentBuffer = malloc(contentBufferSize);
  if (contentBuffer == NULL) {
    perror("Failed to allocate memory for contentBuffer");
    free(itemsBuffer);
    free(home_blog_items);
    free((void *)blog_container_html);
    free((void *)blog_entry_html);
    free((void *)element_paragraph_html);
    free((void *)element_tittle_html);
    free((void *)element_image_html);
    free((void *)element_image_paragraph_html);
    free((void *)element_date_time_html);
    free((void *)element_link_html);
    free((void *)element_byline_html);
    free((void *)element_image_gallery_html);
    free((void *)element_gallery_container_html);
    free((void *)element_gallery_row_html);
    free((void *)element_gallery_item_html);
    return NULL;
  }

  // Format the final HTML content
  snprintf(contentBuffer, contentBufferSize, blog_container_html, itemsBuffer);

  // Free the itemsBuffer as it's no longer needed
  free(itemsBuffer);

  // Free the blog items
  free(home_blog_items);

  // Free the templates
  free((void *)blog_container_html);
  free((void *)blog_entry_html);

  return contentBuffer;
}
