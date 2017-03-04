function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6334\" class=\"headerLeftMenuInActive\"><a id=\"aID6334\" href=\"#\" OnMouseOver=\"link('_dir','logical0',this)\" class=\"leftMenuLinkHeadInActive\">logical</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6333\" class=\"leftMenuInActive\"><a id=\"aID6333\" href=\"#\" OnMouseOver=\"link('_dir','local_folder/local_folder0',this)\" class=\"leftMenuLinkInActive\">local_folder</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID830\" class=\"leftMenuInActive\"><a id=\"aID830\" href=\"#\" OnMouseOver=\"link('_class','LogicalEntry35340',this)\" class=\"leftMenuLinkInActive\">LogicalEntry</a></div>\n");
document.write("<div id=\"divID831\" class=\"leftMenuInActive\"><a id=\"aID831\" href=\"#\" OnMouseOver=\"link('_class','LogicalFileEntry35340',this)\" class=\"leftMenuLinkInActive\">LogicalFileEntry</a></div>\n");
document.write("<div id=\"divID832\" class=\"leftMenuInActive\"><a id=\"aID832\" href=\"#\" OnMouseOver=\"link('_class','LogicalMountPoint35340',this)\" class=\"leftMenuLinkInActive\">LogicalMountPoint</a></div>\n");
document.write("<div id=\"divID833\" class=\"leftMenuInActive\"><a id=\"aID833\" href=\"#\" OnMouseOver=\"link('_class','Path35340',this)\" class=\"leftMenuLinkInActive\">Path</a></div>\n");
document.write("<div id=\"divID834\" class=\"leftMenuInActive\"><a id=\"aID834\" href=\"#\" OnMouseOver=\"link('_class','System35340',this)\" class=\"leftMenuLinkInActive\">System</a></div>\n");
document.write("<div id=\"divID6169\" class=\"leftMenuInActive\"><a id=\"aID6169\" href=\"#\" OnMouseOver=\"link('_class','TreeNode0',this)\" class=\"leftMenuLinkInActive\">TreeNode</a></div>\n");
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
