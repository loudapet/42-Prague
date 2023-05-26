/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:03:43 by plouda            #+#    #+#             */
/*   Updated: 2023/05/26 11:06:51 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* CELEBP27 */
#define _OPEN_THREADS
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void *thread(void *arg)
{
  char *ret;
  char *str;

  str = arg;
  printf("thread() entered with argument '%s'\n", str);
  if ((ret = (char*) malloc(20)) == NULL) {
    perror("malloc() error");
    exit(2);
  }
  strcpy(ret, "This is a test");
  pthread_exit(ret);
}

int	main() {
  pthread_t thid;
  void *ret;

  if (pthread_create(&thid, NULL, thread, "thread 1") != 0) {
    perror("pthread_create() error");
    exit(1);
  }

  if (pthread_join(thid, &ret) != 0) {
    perror("pthread_create() error");
    exit(3);
  }

  printf("thread exited with '%s'\n", (char *)ret);
}