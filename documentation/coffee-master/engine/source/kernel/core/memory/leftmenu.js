function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6298\" class=\"headerLeftMenuInActive\"><a id=\"aID6298\" href=\"#\" OnMouseOver=\"link('_dir','memory0',this)\" class=\"leftMenuLinkHeadInActive\">memory</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID763\" class=\"leftMenuInActive\"><a id=\"aID763\" href=\"#\" OnMouseOver=\"link('_class','Allocator58373',this)\" class=\"leftMenuLinkInActive\">Allocator</a></div>\n");
document.write("<div id=\"divID764\" class=\"leftMenuInActive\"><a id=\"aID764\" href=\"#\" OnMouseOver=\"link('_class','AllocatorDefault58373',this)\" class=\"leftMenuLinkInActive\">AllocatorDefault</a></div>\n");
document.write("<div id=\"divID765\" class=\"leftMenuInActive\"><a id=\"aID765\" href=\"#\" OnMouseOver=\"link('_class','MemoryManager58373',this)\" class=\"leftMenuLinkInActive\">MemoryManager</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Functions</div>\n");
document.write("<div id=\"divID2392\" class=\"leftMenuInActive\"><a id=\"aID2392\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Compare3816260353',this)\" class=\"leftMenuLinkInActive\">COFFEE_Compare</a></div>\n");
document.write("<div id=\"divID2391\" class=\"leftMenuInActive\"><a id=\"aID2391\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Copy1176647169',this)\" class=\"leftMenuLinkInActive\">COFFEE_Copy</a></div>\n");
document.write("<div id=\"divID2386\" class=\"leftMenuInActive\"><a id=\"aID2386\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_CoreMemoryAllocate1644753551',this)\" class=\"leftMenuLinkInActive\">COFFEE_CoreMemoryAllocate</a></div>\n");
document.write("<div id=\"divID2387\" class=\"leftMenuInActive\"><a id=\"aID2387\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_CoreMemoryFree1714437850',this)\" class=\"leftMenuLinkInActive\">COFFEE_CoreMemoryFree</a></div>\n");
document.write("<div id=\"divID2388\" class=\"leftMenuInActive\"><a id=\"aID2388\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_CoreMemoryReallocate797289405',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('COFFEE_CoreMemoryReallocate');\" onmouseout=\"return nd();\">COFFEE_CoreMemoryRealloca.<img src=\"../../../../../../common/menunametolong.gif\"border=0></a></div>\n");
document.write("<div id=\"divID2400\" class=\"leftMenuInActive\"><a id=\"aID2400\" href=\"#\" OnMouseOver=\"link('_member','coffee_delete818781299',this)\" class=\"leftMenuLinkInActive\">coffee_delete<></a></div>\n");
document.write("<div id=\"divID2408\" class=\"leftMenuInActive\"><a id=\"aID2408\" href=\"#\" OnMouseOver=\"link('_member','coffee_delete_array818781299',this)\" class=\"leftMenuLinkInActive\">coffee_delete_array<></a></div>\n");
document.write("<div id=\"divID2389\" class=\"leftMenuInActive\"><a id=\"aID2389\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_GetAllocationSize86143056',this)\" class=\"leftMenuLinkInActive\">COFFEE_GetAllocationSize</a></div>\n");
document.write("<div id=\"divID2399\" class=\"leftMenuInActive\"><a id=\"aID2399\" href=\"#\" OnMouseOver=\"link('_member','coffee_new1001407150',this)\" class=\"leftMenuLinkInActive\">coffee_new<></a></div>\n");
document.write("<div id=\"divID2407\" class=\"leftMenuInActive\"><a id=\"aID2407\" href=\"#\" OnMouseOver=\"link('_member','coffee_new_array273823323',this)\" class=\"leftMenuLinkInActive\">coffee_new_array<></a></div>\n");
document.write("<div id=\"divID2390\" class=\"leftMenuInActive\"><a id=\"aID2390\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Set446227529',this)\" class=\"leftMenuLinkInActive\">COFFEE_Set</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Macros</div>\n");
document.write("<div id=\"divID579\" class=\"leftMenuInActive\"><a id=\"aID579\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Allocate1459865',this)\" class=\"leftMenuLinkInActive\">COFFEE_Allocate</a></div>\n");
document.write("<div id=\"divID583\" class=\"leftMenuInActive\"><a id=\"aID583\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Delete3261420847',this)\" class=\"leftMenuLinkInActive\">COFFEE_Delete</a></div>\n");
document.write("<div id=\"divID585\" class=\"leftMenuInActive\"><a id=\"aID585\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_DeleteArray3261420847',this)\" class=\"leftMenuLinkInActive\">COFFEE_DeleteArray</a></div>\n");
document.write("<div id=\"divID580\" class=\"leftMenuInActive\"><a id=\"aID580\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Free3261420847',this)\" class=\"leftMenuLinkInActive\">COFFEE_Free</a></div>\n");
document.write("<div id=\"divID582\" class=\"leftMenuInActive\"><a id=\"aID582\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_New1468131',this)\" class=\"leftMenuLinkInActive\">COFFEE_New</a></div>\n");
document.write("<div id=\"divID584\" class=\"leftMenuInActive\"><a id=\"aID584\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_NewArray4007711635',this)\" class=\"leftMenuLinkInActive\">COFFEE_NewArray</a></div>\n");
document.write("<div id=\"divID581\" class=\"leftMenuInActive\"><a id=\"aID581\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Reallocate3580845809',this)\" class=\"leftMenuLinkInActive\">COFFEE_Reallocate</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
