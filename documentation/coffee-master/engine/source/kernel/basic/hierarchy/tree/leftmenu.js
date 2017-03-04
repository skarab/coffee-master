function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6281\" class=\"headerLeftMenuInActive\"><a id=\"aID6281\" href=\"#\" OnMouseOver=\"link('_dir','tree0',this)\" class=\"leftMenuLinkHeadInActive\">tree</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID741\" class=\"leftMenuInActive\"><a id=\"aID741\" href=\"#\" OnMouseOver=\"link('_class','TreeNode6216',this)\" class=\"leftMenuLinkInActive\">TreeNode<></a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1162\" class=\"leftMenuInActive\"><a id=\"aID1162\" href=\"#\" OnMouseOver=\"link('_member','TreeNode7578827',this)\" class=\"leftMenuLinkInActive\">TreeNode</a></div>\n");
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
