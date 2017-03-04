function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6470\" class=\"headerLeftMenuInActive\"><a id=\"aID6470\" href=\"#\" OnMouseOver=\"link('_dir','mesh0',this)\" class=\"leftMenuLinkHeadInActive\">mesh</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1054\" class=\"leftMenuInActive\"><a id=\"aID1054\" href=\"#\" OnMouseOver=\"link('_class','MeshOBJ22463',this)\" class=\"leftMenuLinkInActive\">MeshOBJ</a></div>\n");
document.write("<div id=\"divID1055\" class=\"leftMenuInActive\"><a id=\"aID1055\" href=\"#\" OnMouseOver=\"link('_class','MeshOBJFile22463',this)\" class=\"leftMenuLinkInActive\">MeshOBJFile</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Functions</div>\n");
document.write("<div id=\"divID5515\" class=\"leftMenuInActive\"><a id=\"aID5515\" href=\"#\" OnMouseOver=\"link('_member','MeshModifierComputeAdjacency1087120827',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('MeshModifierComputeAdjacency');\" onmouseout=\"return nd();\">MeshModifierComputeAdjace.<img src=\"../../../../../common/menunametolong.gif\"border=0></a></div>\n");
document.write("<div id=\"divID5514\" class=\"leftMenuInActive\"><a id=\"aID5514\" href=\"#\" OnMouseOver=\"link('_member','MeshModifierComputeTBN1087120827',this)\" class=\"leftMenuLinkInActive\">MeshModifierComputeTBN</a></div>\n");
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
