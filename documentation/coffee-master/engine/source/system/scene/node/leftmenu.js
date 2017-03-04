function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6407\" class=\"headerLeftMenuInActive\"><a id=\"aID6407\" href=\"#\" OnMouseOver=\"link('_dir','node0',this)\" class=\"leftMenuLinkHeadInActive\">node</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID927\" class=\"leftMenuInActive\"><a id=\"aID927\" href=\"#\" OnMouseOver=\"link('_class','Instance42087',this)\" class=\"leftMenuLinkInActive\">Instance</a></div>\n");
document.write("<div id=\"divID928\" class=\"leftMenuInActive\"><a id=\"aID928\" href=\"#\" OnMouseOver=\"link('_class','Node42087',this)\" class=\"leftMenuLinkInActive\">Node</a></div>\n");
document.write("<div id=\"divID6190\" class=\"leftMenuInActive\"><a id=\"aID6190\" href=\"#\" OnMouseOver=\"link('_class','TreeNode0',this)\" class=\"leftMenuLinkInActive\">TreeNode</a></div>\n");
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
